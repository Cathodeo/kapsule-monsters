#include <allegro.h>
#include <stdio.h>
#include "ui.h"
#include "palette.h"
#include "images.h"
#include "overworldmap.h"
#include "events.h"
#include "charas.h"
#include "battlecomputes.h"
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

 
int c;
init_battle(40, 38);

while (1) {
    c = readkey();   // waits for key press
    switch (c >> 8) { // high byte is the key code
        case KEY_1:
            battle_flow(0, speed_check());
            break;
        case KEY_2:
            battle_flow(1, speed_check());
            break;
        case KEY_ESC:
            return 0;
    }
}


allegro_exit(); // Clean up Allegro
return 0; // Ensure the function ends correctly

}
