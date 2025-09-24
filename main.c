#include <allegro.h>
#include <stdio.h>
#include "ui.h"
#include "palette.h"
#include "images.h"
#include "overworldmap.h"
#include "events.h"
#include "charas.h"

//DEBUG: to remove or move to another file



//Main file. The target of this file is to//
//Simply initialize the library and processes//
//The goal is to have as few processes here as possible//


//Main loop. Exits the program on termination

int main(void) {

//Initialize Allegro 4.22 library and keyboard tracking

//For further err-or handling
 int err;
//This is the provisional spritesheet, moving to other files later:
 const char *sheet_file = "CHARAS.PCX";
 
 chdir("/home/tmmartin/KAPSULE");
 allegro_init();
 install_keyboard();

//Set color depth to 8 bits. The game is going to 
//use a palette of 4 shades of monochrome. 255 colors is enough
 set_color_depth(8);


 //Set the window size (Provisional, debugging)

if (set_gfx_mode(GFX_XWINDOWS, 640, 480, 0, 0) != 0) {
    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
    allegro_message("Unable to set any graphic mode\n%s\n", allegro_error);
    return 1;
    }

 /* Load + slice */
    err = load_and_cache_sheet("CHARAS.PCX", CHAR_COUNT);
    if (err) {
        allegro_message("load_and_cache_sheet failed (%d)", err);
        return 2;
    }

 buffer = create_bitmap(SCREEN_W, SCREEN_H);
    if (!buffer) {
        allegro_message("Failed to create buffer!");
        return -1;
    }

     init_map("TESTMAP.PCX");

      int tick = 0;

while (!key[KEY_ESC]) {


   


    
    rest(16); // ~60 FPS
}

allegro_exit(); // Clean up Allegro
return 0; // Ensure the function ends correctly

}
