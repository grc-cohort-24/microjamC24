#pragma once

#include "ugb/ugb_entity.h"

namespace ugb
{

    class Player : public Entity
    {
    public:
        // player needs position and speed
        Player(bn::fixed_point start_position, bn::fixed speed);

        // update
        void update();

    private:
        int _animation_counter;
        bool _is_fish2;

        void _update_position();
        void _update_animation();
    };

}