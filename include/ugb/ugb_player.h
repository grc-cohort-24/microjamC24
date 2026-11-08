#pragma once

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>

namespace ugb {

class ugb_player {
    public:
        // player needs position and speed
        ugb_player(bn::fixed_point start_position, bn::fixed speed);

        //update
        void update();

        // player.x and player.y
        bn::fixed x() const;
        bn::fixed y() const;

    private:
        bn::sprite_ptr _sprite;
        bn::fixed _speed;

        int _animation_counter = 0;
        bool _is_fish2 = false;

        void _update_position();
        void _update_animation();
    };

}