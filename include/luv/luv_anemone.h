#pragma once

#include <bn_display.h>
#include <bn_sprite_ptr.h>
#include <bn_rect.h>
#include <bn_fixed.h>
#include <bn_size.h>
#include "luv/luv_methods.h"
#include <bn_sprite_animate_actions.h>

// Create a namespace to ensure all variables within are scoped to the instance.
namespace luv
{
    class luv_anemone
    {

        /**
         * Anemone constructor
         */
    public:
        luv_anemone(bn::fixed_point spawn);

        bn::rect get_bounding_box();

        void _update_animation();

    private:
        bn::fixed _pos_x;
        bn::fixed _pos_y;
        bn::sprite_ptr _sprite;
        bn::size _size;
        bn::rect _bounding_box; // Bounding box of the anemone
        bn::sprite_animate_action<10> _sprite_action;
    };
}