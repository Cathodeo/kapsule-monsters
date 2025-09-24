#include "charas.h"


/*Mapping the directions to numbers for convenience:*/


/* global cache: frames[char_id][direction][frame_index]
* frame_index: 0 = static, 1 = anim frame 1, 2 = anim frame 2
*/

static BITMAP *frames[CHAR_COUNT][DIR_COUNT][FRAME_COUNT];
static int frames_loaded = 0;

/* utility: create an empty bitmap with the same color depth as "ref"
* and clear it to the mask color (so masked_blit works right away)
*/
static BITMAP *create_blank_like(BITMAP *ref)
{
    int depth = bitmap_color_depth(ref);
    BITMAP *b = create_bitmap_ex(depth, TILE_W, TILE_H);
    if (!b) return NULL;
    clear_to_color(b, bitmap_mask_color(b));
    return b;
}

/* helper: copy a rectangle from (CHARAS.PCX for the time being) into a newly allocated bitmap 
* uses masked_blit so transparency is preserved (expects same color depths)
*/
static BITMAP *slice_copy(BITMAP *sheet, int sx, int sy)
{
    if (!sheet) return NULL;
    BITMAP *dst = create_blank_like(sheet);
    if (!dst) return NULL;
    /* masked_blit requires same color depth for source & dest */
    masked_blit(sheet, dst, sx, sy, 0, 0, TILE_W, TILE_H);
    return dst;
}

/* create a horizontally flipped copy of src into a new bitmap.
*  this is basically for the LEFT direction that is not on CHARAS.PCX
*/
static BITMAP *create_hflip_copy(BITMAP *src)
{
    if (!src) return NULL;
    /* create a dst with the same depth as src */
    BITMAP *dst = create_blank_like(src);
    if (!dst) return NULL;
    /* draw_sprite_h_flip respects the mask color */
    draw_sprite_h_flip(dst, src, 0, 0);
    return dst;
}

/* load the sheet and slice it into frames[][][].
* filename: CHARAS.PCX for the moment being
* char_count: number of vertical character rows to slice -> 40 on CHARAS.PCX
* Returns 0 on success, non-zero on error.
*
* Layout assumptions:
* - Each row (y = char_id * TILE_H) is a different character.
* - Static frames on columns: DOWN=0, UP=1, RIGHT=2
* - Animated frames on columns: DOWN=(5,6), UP=(7,8), RIGHT=(9,10)
* - LEFT is mirrored RIGHT (we pre-generate left by h-flipping right frames)
*/

int load_and_cache_sheet(const char *filename, int char_count)
{
    int i, d, f;
    BITMAP *sheet = NULL;

    if (char_count > CHAR_COUNT) {
        fprintf(stderr, "Requested char_count (%d) > CHAR_COUNT (%d)\n", char_count, CHAR_COUNT);
        return -1;
    }

    sheet = load_bitmap(filename, NULL);
    if (!sheet) {
        fprintf(stderr, "Failed to load sheet '%s'\n", filename);
        return -2;
    }

    /* sanity checks */
    if (sheet->h < char_count * TILE_H) {
        fprintf(stderr, "Sheet too short: height=%d, needed=%d\n", sheet->h, char_count * TILE_H);
        destroy_bitmap(sheet);
        return -3;
    }

    /* columns check is lenient; just ensure we can read required columns */
    if (sheet->w < (11 + 1) * TILE_W) {
        /* we access up to column 10 (0-based) in layout, so require 11 columns */
        fprintf(stderr, "Warning: sheet width seems small (%d). Expected at least %d columns (for columns up to 10).\n",
                sheet->w, (11 + 1));
        /* continue anyway; masked_blit will fail if out-of-bounds */
    }

    /* clear any previous cache (defensive) */
    for (i = 0; i < CHAR_COUNT; ++i)
        for (d = 0; d < DIR_COUNT; ++d)
            for (f = 0; f < FRAME_COUNT; ++f)
                frames[i][d][f] = NULL;

    /* column mapping */
    const int static_col[3] = { 0, 1, 2 };    /* DOWN, UP, RIGHT */
    const int anim_base[3] = { 5, 7, 9 };     /* base columns for DOWN,UP,RIGHT (two frames each) */

    for (i = 0; i < char_count; ++i) {
        int sy = i * TILE_H;

        /* static frames (frame index 0) */
        for (d = 0; d < 3; ++d) {
            int col = static_col[d];
            frames[i][d][0] = slice_copy(sheet, col * TILE_W, sy);
            if (!frames[i][d][0]) {
                fprintf(stderr, "Failed to slice static frame for char %d dir %d\n", i, d);
                /* continue trying, but note failure */
            }
        }

        /* animated frames (1 and 2) */
        for (d = 0; d < 3; ++d) {
            for (f = 0; f < 2; ++f) {
                int col = anim_base[d] + f; /* f==0 -> first anim frame */
                frames[i][d][1 + f] = slice_copy(sheet, col * TILE_W, sy);
                if (!frames[i][d][1 + f]) {
                    fprintf(stderr, "Failed to slice anim frame for char %d dir %d frame %d\n", i, d, f);
                }
            }
        }

        /* LEFT (mirror of RIGHT) - pre-generate copies */
        for (f = 0; f < FRAME_COUNT; ++f) {
            if (frames[i][DIR_RIGHT][f]) {
                frames[i][DIR_LEFT][f] = create_hflip_copy(frames[i][DIR_RIGHT][f]);
                if (!frames[i][DIR_LEFT][f]) {
                    fprintf(stderr, "Failed to create flipped frame for char %d frame %d\n", i, f);
                }
            } else {
                frames[i][DIR_LEFT][f] = NULL;
            }
        }
    }

    destroy_bitmap(sheet);
    frames_loaded = 1;
    return 0;
}

/* draw a character using the cached frames. anim_frame must be 0..2
 * dest can be screen or any bitmap of compatible color depth.
 */
void draw_chara(int char_id, enum Direction dir, int anim_frame, BITMAP *dest, int dx, int dy)
{
    if (!frames_loaded) return;
    if (char_id < 0 || char_id >= CHAR_COUNT) return;
    if (dir < 0 || dir >= DIR_COUNT) return;
    if (anim_frame < 0 || anim_frame >= FRAME_COUNT) anim_frame = 0;

    BITMAP *bmp = frames[char_id][dir][anim_frame];
    if (!bmp) return;

    /* masked_blit: source, dest, sx, sy, dx, dy, w, h */
    masked_blit(bmp, dest, 0, 0, dx, dy, TILE_W, TILE_H);
}

/* free everything */
void destroy_frames()
{
    int i, d, f;
    for (i = 0; i < CHAR_COUNT; ++i) {
        for (d = 0; d < DIR_COUNT; ++d) {
            for (f = 0; f < FRAME_COUNT; ++f) {
                if (frames[i][d][f]) {
                    destroy_bitmap(frames[i][d][f]);
                    frames[i][d][f] = NULL;
                }
            }
        }
    }
    frames_loaded = 0;
}

