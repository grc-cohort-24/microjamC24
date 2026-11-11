#pragma once

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>

namespace vct {

class player {
        //Screen bounds
        static constexpr int MAX_X = bn::display::width() / 2;

        static constexpr int MIN_X = -bn::display::width() / 2;

        static constexpr int MAX_Y = bn::display::height() / 2;
        
        static constexpr int MIN_Y = -bn::display::height() / 2;

    public:
        //Player constructor
        player(bn::fixed_point starting_position, bn::fixed speed);
        
        //Constantly updates the game
        void update();
        
        //Returns true or false based on whether
        //the player has left the screen
        bool out_of_bounds() const;
    
    private:
        //Player sprite
        bn::sprite_ptr _sprite;
        
        //Player speed
        bn::fixed _speed;

        //Similarly to update, but now directly
        //updates the player (movement) instead
        void _update_position();
};

}