#ifndef OVERWORLDMAP_H
#define OVERWORLDMAP_H


#include <allegro.h>
#include <stdio.h>

extern BITMAP *viewport;
extern int viewx;
extern int viewy;
void init_map(const char *map_path);
void draw_viewport(int x, int y);
void scroll_to(int *viewx, int *viewy, int target_x, int target_y);

#endif