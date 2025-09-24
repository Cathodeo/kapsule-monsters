#include <palette.h>
#include <allegro.h>

PALETTE pal;

// Testing the default grayscale palette
void set_pal_grayscale(){
pal[0].r = pal[0].g = pal[0].b = 0;   // black
pal[1].r = pal[1].g = pal[1].b = 21;  // dark gray
pal[2].r = pal[2].g = pal[2].b = 42;  // light gray
pal[3].r = pal[3].g = pal[3].b = 63;  // white
set_palette(pal);
}

// Testing a palette swap to a different palette
void set_pal_sephia(){
pal[0].r = 10; pal[0].g = 5;  pal[0].b = 0;
pal[1].r = 20; pal[1].g = 15; pal[1].b = 5;
pal[2].r = 40; pal[2].g = 30; pal[2].b = 10;
pal[3].r = 63; pal[3].g = 55; pal[3].b = 20;
set_palette(pal);
}
