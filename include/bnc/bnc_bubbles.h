#pragma once 
#include <bn_fixed.h>
#include <bn_sprite_ptr.h>

namespace bnc {

    // static constexpr int _BUBBLES_MIN_Y = -bn::display::height() / 2;
    // static constexpr int _BUBBLES_MAX_Y = bn::display::height() / 2;
    // static constexpr int _BUBBLES_MIN_X = -bn::display::width() / 2;        
    // static constexpr int _BUBBLES_MAX_X = bn::display::width() / 2;

    static constexpr int _BUBBLE_MIN_SPEED = 0.5;
    static constexpr int _BUBBLE_MAX_SPEED = 1.5;



    class Bubbles{


        public:
        Bubbles(bn::fixed bubble_x, bn::fixed bubble_y, bn::fixed bubble_speed);

        void update();

        private:
        bn::sprite_ptr _bubble;
        bn::fixed _bubble_speed;

    };
}

