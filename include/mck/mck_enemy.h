#pragma once

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>
#include <bn_rect.h>
#include <bn_random.h>

#include "mj/mj_game.h"
#include "mck/mck_bounds.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace mck {

/**
 * An obstacle character not controlled by the player.
 */
class enemy {
        // The bounds of the screen
        static constexpr int SPAWN_MARGIN = 16; 
        static constexpr int NUM_SIDES = 4;

    public:
        /**
         * enemy constructor
         * 
         * @param speed the enemy's speed
         * @param data the current game data, used for random number generation
         */
        enemy(bn::fixed speed, bn::random& random);

        bn::rect hitbox() const;

        /**
         * Moves the enemy based on its x and y speed
         */
        void update();
    
    private:
        // The sprite to display the enemy
        bn::sprite_ptr _sprite;
        // The pixels/frame the enemy moves in each dimension
        bn::fixed _xspeed;
        bn::fixed _yspeed;

        /**
         * Moves the enemy based on its current x and y speeds
         */
        void _update_position();
        
};

}
