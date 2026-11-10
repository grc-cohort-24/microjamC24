#pragma once

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>

#include "ugb/ugb_entity.h"

namespace ugb
{

    class player : public entity
    {
    public:
        // player needs position and speed
        player(bn::fixed_point start_position, bn::fixed speed);

        // update
        void update();

    private:
        int _animation_counter;
        bool _is_fish2;

        void _update_position();
        void _update_animation();
    };

}