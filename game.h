#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdbool.h>

// Screen dimensions for Apple II text mode
#define SCREEN_W 40
#define SCREEN_H 24

// Logging
#define MAX_LOG_LINES 4
#define LOG_LINE_LEN 38

// Game Constants (Scaled down for integer math/loop cycles)
#define FIRE_MAX_LEVEL 4
#define FIRE_COOL_TICKS 300 // Approx cycles before fire dies down
#define STOKE_COST 1
#define LIGHT_COST 5

// State Structure
typedef struct {
    uint16_t wood;
    uint16_t fur;
    uint16_t meat;
    
    // Fire
    uint8_t fire_level;       // 0=Dead, 1=Smoldering, 2=Flickering, 3=Burning, 4=Roaring
    uint16_t fire_timer;      // Ticks until fire level drops
    
    // Flags
    bool fire_lit_once;
    bool builder_active;
    
    // UI State
    char log_buffer[MAX_LOG_LINES][LOG_LINE_LEN + 1];
    uint8_t log_head; // Index of the newest message
    char status_msg[40];

} GameState;

extern GameState state;

// --- Logic (logic.c) ---
void game_init(void);
void game_tick(void);
void action_light_fire(void);
void action_stoke_fire(void);
void action_gather_wood(void); // Simple debug/initial action to get wood

// --- UI (ui.c) ---
void ui_init(void);
void ui_draw(void);
void ui_log(const char* msg);
void ui_set_status(const char* msg);

#endif
