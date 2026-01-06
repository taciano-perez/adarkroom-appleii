#include "game.h"
#include <string.h>
#include <stdio.h>

// Fire descriptions matching the JS source
const char* FIRE_DESC[] = {
    "dead",
    "smoldering",
    "flickering",
    "burning",
    "roaring"
};

void game_init(void) {
    state.wood = 0; // Start with 0 (or 20 for testing)
    state.fur = 0;
    state.meat = 0;
    state.fire_level = 0;
    state.fire_timer = 0;
    state.fire_lit_once = false;
    state.builder_active = false;
    
    // Clear log buffer
    memset(state.log_buffer, 0, sizeof(state.log_buffer));
    state.log_head = 0;
    
    // Just for testing, give some starter wood if needed, 
    // but original game starts with nothing and a button to "light fire" appears when you have wood? 
    // Actually in original, you stumble in. We'll simulate 'gather' to bootstrap.
    state.wood = 10; 
}

void game_tick(void) {
    char buf[30];
    // Handle Fire Cooling
    if (state.fire_level > 0) {
        state.fire_timer++;
        if (state.fire_timer > FIRE_COOL_TICKS) {
            state.fire_level--;
            state.fire_timer = 0;
            
            sprintf(buf, "the fire is %s.", FIRE_DESC[state.fire_level]);
            ui_log(buf);
            
            if (state.fire_level == 0) {
                ui_log("the room is freezing.");
            }
        }
    }
}

void action_light_fire(void) {
    if (state.fire_level > 0) {
        ui_log("the fire is already lit.");
        return;
    }
    
    if (state.wood < LIGHT_COST) {
        ui_log("not enough wood.");
        return;
    }
    
    state.wood -= LIGHT_COST;
    state.fire_level = 1; // Start smoldering or burning? JS says Burning (3) on light, but let's be gradual or stick to source.
    // script/room.js: $SM.set('game.fire', Room.FireEnum.Burning); -> Burning is 3.
    state.fire_level = 3; 
    state.fire_timer = 0;
    state.fire_lit_once = true;
    
    ui_log("fire burning. room is warm.");
}

void action_stoke_fire(void) {
    char buf[30];

    if (state.fire_level == 0) {
        ui_log("fire is dead.");
        return;
    }
    
    if (state.wood < STOKE_COST) {
        ui_log("wood has run out.");
        return;
    }
    
    state.wood -= STOKE_COST;
    state.fire_timer = 0; // Reset cool timer
    
    if (state.fire_level < FIRE_MAX_LEVEL) {
        state.fire_level++;
    }
    
    sprintf(buf, "the fire is %s.", FIRE_DESC[state.fire_level]);
    ui_log(buf);
}

void action_gather_wood(void) {
    // Placeholder for "Outside" or initial gathering
    state.wood += 5;
    ui_log("gathered wood.");
}
