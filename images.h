#ifndef IMAGES_H
#define IMAGES_H


#include <allegro.h>


extern BITMAP *buffer;

void load_blit(const char *image_path, int dst_x, int dst_y);

#endif