#include <conio.h>
#include <string.h>
#include <stdio.h>
#include "game.h"

void ui_init(void) {
    clrscr();
}

void ui_log(const char* msg) {
    // Shift lines up
    // Simple circular buffer or shift approach.
    // Let's do shift for simplicity in display, though array rotate is better.
    // For small depth (4-5 lines), copy is fine.
    
    int i;
    for (i = MAX_LOG_LINES - 1; i > 0; i--) {
        strncpy(state.log_buffer[i], state.log_buffer[i-1], LOG_LINE_LEN);
    }
    // Insert new at 0
    strncpy(state.log_buffer[0], msg, LOG_LINE_LEN);
    // Ensure null termination
    state.log_buffer[0][LOG_LINE_LEN] = '\0';
    
    ui_draw();
}

void draw_frame(void) {
    // Draw a separator line
    gotoxy(0, 5);
    cprintf("----------------------------------------");
}

void ui_draw(void) {
    int i;
    
    // 1. Status Area (Top)
    gotoxy(0, 0);
    // Pad to clear line
    cprintf("%-40s", state.room_name);
    
    gotoxy(0, 2);
    // Clearing line logic manually or just overwrite with spaces if needed
    // Apple II text mode doesn't auto-clear unless we tell it.
    cprintf("Wood: %4d   Fire: %d/4   ", state.wood, state.fire_level);
    
    // 2. Notification Log (Middle)
    draw_frame();
    for (i = 0; i < MAX_LOG_LINES; i++) {
        gotoxy(0, 6 + i);
        // Pad with spaces to clear previous text
        cprintf("%-38s", state.log_buffer[i]); 
    }
    
    draw_frame();
    gotoxy(0, 11);
    cprintf("----------------------------------------");
    
    // 3. Actions / Menu (Bottom)
    gotoxy(0, 13);
    if (state.fire_level == 0) {
        if (!state.fire_lit_once) {
            cprintf("[A] Light Fire            ");
        } else if (state.wood >= LIGHT_COST) {
            cprintf("[A] Light Fire (5 wood)   ");
        } else {
             cprintf("                          ");
        }
    } else if (state.fire_level > 0) {
        cprintf("[S] Stoke Fire (1 wood)   ");
    } else {
        cprintf("                          "); // Clear
    }
    
    gotoxy(0, 15);
    if (state.fire_lit_once) {
        cprintf("[G] Gather Wood           ");
    } else {
        cprintf("                          ");
    }
    
    gotoxy(0, 23);
    cprintf("Ready.");
}
