#include "images.h"
#include <allegro.h>

BITMAP *buffer = NULL;


void load_blit(const char *image_path, int dst_x, int dst_y) {
    // Load the new image from the specified path
    BITMAP *image = load_pcx(image_path, NULL);
    if (!image) {
        allegro_message("Failed to load image: %s", image_path);
        return;
    }

    // Create a temporary buffer for rendering the effect
    BITMAP *temp_buffer = create_bitmap(buffer->w, buffer->h);
    if (!temp_buffer) {
        allegro_message("Failed to create temporary buffer.");
        destroy_bitmap(image);
        return;
    }

    int num_bars = 32; // Number of bars (adjust for more/less bars)
    int bar_height = SCREEN_H / num_bars; // Height of each bar
    int transition_speed = 4; // Speed of transition (lower is faster)

    // Transition effect loop
    for (int step = 0; step <= bar_height; step += transition_speed) {
        // Clear the temporary buffer
        clear(temp_buffer);

        // Loop through each bar
        for (int i = 0; i < num_bars; i++) {
            // For even bars, reveal from top to bottom
            if (i % 2 == 0) {
                masked_blit(image, temp_buffer, 0, i * bar_height, dst_x, dst_y + i * bar_height, image->w, step);
            } 
            // For odd bars, reveal from bottom to top
            else {
                masked_blit(image, temp_buffer, 0, (i + 1) * bar_height - step, dst_x, dst_y + i * bar_height, image->w, step);
            }
        }
		
        // Blit the temp buffer onto the main buffer
        blit(temp_buffer, buffer, 0, 0, 0, 0, buffer->w, buffer->h);

        // Display the buffer on screen
        vsync();  // Ensure smooth transitions
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        rest(20);  // Control the speed of the effect
    }
    // Once the transition is complete, blit the new image fully
    blit(image, buffer, 0, 0, dst_x, dst_y, image->w, image->h);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    // Clean up
    destroy_bitmap(image);
    destroy_bitmap(temp_buffer);
}

