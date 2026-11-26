#pragma once

#include <bn_sprite_ptr.h>
#include <bn_rect.h>
#include <bn_sprite_animate_actions.h>
#include <bn_size.h>
#include "luv/luv_methods.h"

// Create a namespace to ensure all variables within are scoped to the instance.
namespace luv
{
    class luv_trap
    {

    public:
        luv_trap(bn::fixed_point spawn);

        //Get the trap jellyfish bounding box
        bn::rect get_bounding_box();

        //Update the trap's current frame
        void update_trap_animation();

        //Update the float position of the trap
        void update_float(int seconds);

        //Move the jellyfish up
        void float_up();

        //Move the jellyfish down
        void float_down();

    private:
        static constexpr int ANEMONE_SIZE = 16;
        bn::sprite_ptr _sprite;
        bn::size _size;
        bn::rect _bounding_box; // Bounding box of the trap anemone
        bn::sprite_animate_action<8> _sprite_action;
    };
}