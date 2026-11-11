#pragma once

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>

namespace vct {

class player {
        static constexpr int MAX_X = bn::display::width() / 2;

        static constexpr int MIN_X = -bn::display::width() / 2;

        static constexpr int MAX_Y = bn::display::height() / 2;
        
        static constexpr int MIN_Y = -bn::display::height() / 2;

    public:
        player(bn::fixed_point starting_position, bn::fixed speed);
        void update();
        bool out_of_bounds() const;
    
    private:
        bn::sprite_ptr _sprite;
        bn::fixed _speed;

        void _update_position();
};

}