#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

// Global state instance
GameState state;

int main(void) {
    char key;
    uint16_t loop_counter = 0;

    // Initialize systems
    ui_init();
    game_init();

    // Initial message
    ui_log("the fire is dead.");
    ui_log("the room is freezing.");

    // Main Game Loop
    while (1) {
        // 1. Input Handling (Non-blocking)
        if (kbhit()) {
            key = cgetc();
            
            switch (key) {
                case 'a':
                case 'A':
                    action_light_fire();
                    break;
                case 's':
                case 'S':
                    action_stoke_fire();
                    break;
                case 'g':
                case 'G':
                    action_gather_wood();
                    break;
                case 'q': // Quit for testing
                    return 0;
            }
            // Force redraw on input
            ui_draw();
        }

        // 2. Game Logic / Timing
        // We use a simple loop counter for timing as a basic approximation
        // In a real port, you'd use a hardware timer or interrupt
        loop_counter++;
        if (loop_counter > 1000) {
            game_tick();
            loop_counter = 0;
            ui_draw(); // Redraw periodically for status updates
        }
    }
}
