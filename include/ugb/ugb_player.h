#pragma once

#include <bn_sprite_animate_actions.h>

#include "ugb/ugb_entity.h"

namespace ugb
{

    class Player : public Entity
    {
    public:
        // player needs position and speed
        Player(bn::fixed start_x, bn::fixed start_y, bn::fixed speed);

        void update() override;

    private:
        void _update_position();
        void _update_animation();

        bn::sprite_animate_action<2> _animation;
    };

}