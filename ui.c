#include <conio.h>
#include <string.h>
#include <stdio.h>
#include "game.h"

void ui_init(void) {
    clrscr();
}

static void push_log_line(const char* line) {
    int i;
    for (i = MAX_LOG_LINES - 1; i > 0; i--) {
        strncpy(state.log_buffer[i], state.log_buffer[i-1], LOG_LINE_LEN);
    }
    strncpy(state.log_buffer[0], line, LOG_LINE_LEN);
    state.log_buffer[0][LOG_LINE_LEN] = '\0';
}

void ui_log(const char* msg) {
    char lines[10][LOG_LINE_LEN + 1];
    int line_count = 0;
    int len = strlen(msg);
    int start = 0;
    int end;
    int i;
    int remaining;
    int chunk_len;
    int copy_len;
    int split;
    
    // Split message into lines
    while (start < len && line_count < 10) {
        remaining = len - start;
        chunk_len = (remaining > LOG_LINE_LEN) ? LOG_LINE_LEN : remaining;
        
        end = start + chunk_len;
        
        if (end < len && msg[end] != ' ') {
            split = end;
            while (split > start) {
                if (msg[split] == ' ') {
                    end = split;
                    break;
                }
                split--;
            }
        }
        
        copy_len = end - start;
        if (copy_len > LOG_LINE_LEN) copy_len = LOG_LINE_LEN;
        
        strncpy(lines[line_count], msg + start, copy_len);
        lines[line_count][copy_len] = '\0';
        line_count++;
        
        start = end;
        while (start < len && msg[start] == ' ') start++;
    }
    
    for (i = line_count - 1; i >= 0; i--) {
        push_log_line(lines[i]);
    }
    
    ui_draw();
}

void ui_draw_box(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    uint8_t i;

    // Top border
    gotoxy(x1, y1);
    cputc('+');
    for (i = x1 + 1; i < x2; ++i) {
        cputc('-');
    }
    cputc('+');

    // Side borders
    for (i = y1 + 1; i < y2; ++i) {
        gotoxy(x1, i);
        cputc('|');
        gotoxy(x2, i);
        cputc('|');
    }

    // Bottom border
    gotoxy(x1, y2);
    cputc('+');
    for (i = x1 + 1; i < x2; ++i) {
        cputc('-');
    }
    cputc('+');
}

void draw_separator(void) {
    uint8_t i;
    for (i = 0; i < SCREEN_H; ++i) {
        gotoxy(LOG_LINE_LEN, i);
        cputc('|');
    }
}

void ui_draw(void) {
    int i;
    
    // Draw layout lines
    draw_separator();
    
    // --- Column 1: Log ---
    for (i = 0; i < MAX_LOG_LINES; i++) {
        gotoxy(0, i);
        // Limit print width to avoid overrunning separator
        cprintf("%-14s", state.log_buffer[i]); 
    }
    
    // --- Column 2: Buttons ---
    // Clear the button area first (spaces)
    // Area: 15 to 29 (approx)
    for(i = 0; i < 20; i++) {
        gotoxy(15, i);
        cprintf("              "); // 14 spaces
    }

    gotoxy(15, 3);
    if (state.fire_level == 0) {
        if (!state.fire_lit_once) {
            cprintf("[A] light fire");
        } else if (state.wood >= LIGHT_COST) {
            cprintf("[A] light fire");
        }
    } else if (state.fire_level > 0) {
        cprintf("[S] stoke fire");
    }
    
    gotoxy(15, 4);
    if (state.fire_lit_once) {
        cprintf("[G] gather wood");
    }

    // --- Column 3: Store (Boxed) ---
    // Draw Box
    // Height depends on items. Let's fix it to 10 for now.
    ui_draw_box(30, 0, 39, 10);
    
    // Title/Status inside box (or above? Let's put inside)
    gotoxy(31, 1);
    cprintf("Supplies");
    gotoxy(31, 2);
    cprintf("--------");
    
    gotoxy(31, 3);
    cprintf("Wood:%3d", state.wood);
    
    gotoxy(31, 4);
    // Show fire status compactly?
    // "Fire: 4"
    if (state.fire_level > 0) {
         cprintf("Fire:%3d", state.fire_level);
    } else {
         cprintf("Fire:Off");
    }
    
    // Status / Room Name
    gotoxy(15, 1);
    cprintf("%s", state.room_name);

}
