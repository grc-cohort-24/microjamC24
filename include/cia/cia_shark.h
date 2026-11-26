#pragma once

#include <bn_fixed_rect.h>
#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>
#include <bn_random.h>
#include <bn_sprite_animate_actions.h>

#include "cia_player.h"

namespace cia
{
    class shark
    {
    private:
        static constexpr int MAX_X = bn::display::width() / 2 + 20;
        static constexpr int MIN_X = -bn::display::width() / 2 - 20;

    public:
        shark(bn::random &rng, bn::fixed speed);
        void update(cia::player &player);
        bn::fixed_rect rect() const;
        bn::fixed_point getRandomStartPos(bn::random &random) const;

    private:
        bn::sprite_ptr _sprite;
        bn::sprite_animate_action<4> _action;
        bn::fixed _speed;
    };
}