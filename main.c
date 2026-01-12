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
            GameAction actions[MAX_ACTIONS];
            int count;

            key = cgetc();
            count = get_available_actions(actions, MAX_ACTIONS);
            
            // Ensure index is valid before moving
            if (state.active_button_idx >= count) state.active_button_idx = 0;

            switch (key) {
                case 13: // Enter
                    if (count > 0) {
                        perform_action(actions[state.active_button_idx].type);
                    }
                    break;
                case 8:  // Left
                case 11: // Up
                    state.active_button_idx--;
                    if (state.active_button_idx < 0) state.active_button_idx = count - 1;
                    break;
                case 21: // Right
                case 10: // Down
                    state.active_button_idx++;
                    if (state.active_button_idx >= count) state.active_button_idx = 0;
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
