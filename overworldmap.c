#include "overworldmap.h"
#include <allegro.h>

BITMAP *viewport = NULL;
BITMAP *map = NULL;

int viewx = 0;
int viewy = 0;


void init_map(const char *map_path) {
    map = load_pcx(map_path, NULL);       // load full map image
    viewport = create_bitmap(160, 144);   // allocate the viewport buffer
}


void draw_viewport(int x, int y) {
    clear_bitmap(viewport); // optional, avoids leftovers
    blit(map, viewport, x, y, 0, 0, 160, 144);
    stretch_blit(viewport, screen, 0, 0, 160, 144,
                 160, 96, 320, 288);
}


void scroll_to(int *viewx, int *viewy, int target_x, int target_y) {
    while (*viewx != target_x || *viewy != target_y) {
        if (*viewx < target_x) *viewx += 2;
        if (*viewx > target_x) *viewx -= 2;
        if (*viewy < target_y) *viewy += 2;
        if (*viewy > target_y) *viewy -= 2;

        draw_viewport(*viewx, *viewy);
        rest(16);
    }
}



