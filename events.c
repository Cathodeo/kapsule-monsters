#include "events.h"
#include "overworldmap.h"   // (where viewx/viewy live)

void scroll_left() {
    scroll_to(&viewx, &viewy, viewx - 160, viewy);
}

void scroll_right() {
 scroll_to(&viewx, &viewy, viewx + 160, viewy);
}

void scroll_down() {
 scroll_to(&viewx, &viewy, viewx, viewy + 144);
}

void scroll_up() {
    scroll_to(&viewx, &viewy, viewx, viewy - 144);
}