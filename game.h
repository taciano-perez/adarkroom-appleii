#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdbool.h>

// Screen dimensions for Apple II text mode
#define SCREEN_W 40
#define SCREEN_H 24

// UI Layout
#define UI_SEPARATOR_X 12
#define UI_MIDDLE_X 13  // UI_SEPARATOR_X + 1

// Logging
#define MAX_LOG_LINES 20
#define LOG_LINE_LEN UI_SEPARATOR_X

// Game Constants (Scaled down for integer math/loop cycles)
#define FIRE_MAX_LEVEL 4
#define FIRE_COOL_TICKS 300 // Approx cycles before fire dies down
#define STOKE_COST 1
#define LIGHT_COST 5
#define MAX_ACTIONS 10

// State Structure
typedef enum {
    ACTION_LIGHT_FIRE,
    ACTION_STOKE_FIRE,
    ACTION_GATHER_WOOD,
    ACTION_NONE
} ActionType;

typedef struct {
    const char* label;
    ActionType type;
} GameAction;

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
    int8_t active_button_idx; // Index of the currently highlighted button
    char status_msg[40];
    char room_name[40];

} GameState;

extern GameState state;

// --- Logic (logic.c) ---
void game_init(void);
void game_tick(void);
void action_light_fire(void);
void action_stoke_fire(void);
void action_gather_wood(void); // Simple debug/initial action to get wood

int get_available_actions(GameAction* actions, int max_actions);
void perform_action(ActionType type);

// --- UI (ui.c) ---
void ui_init(void);
void ui_draw(void);
void ui_draw_box(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void ui_log(const char* msg);
void ui_set_status(const char* msg);

#endif
