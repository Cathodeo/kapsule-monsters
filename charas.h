#ifndef CHARAS_H
#define CHARAS_H


#define TILE_W 32
#define TILE_H 32
#define CHAR_COUNT 40 /* how many character rows the sheet contains */
#define DIR_COUNT 4 /* down, up, right, left */
#define FRAME_COUNT 3 /* static + 2 animated frames */


#include <allegro.h>
#include <stdio.h>


enum Direction { DIR_DOWN = 0, DIR_UP = 1, DIR_RIGHT = 2, DIR_LEFT = 3 };

static BITMAP *create_blank_like(BITMAP *ref);
static BITMAP *slice_copy(BITMAP *sheet, int sx, int sy);
static BITMAP *create_hflip_copy(BITMAP *src);
int load_and_cache_sheet(const char *filename, int char_count);
void draw_chara(int char_id, enum Direction dir, int anim_frame, BITMAP *dest, int dx, int dy);
void destroy_frames();



#endif