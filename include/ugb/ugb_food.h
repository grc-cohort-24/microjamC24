#pragma once

#include "ugb/ugb_entity.h"

#include <bn_sprite_animate_actions.h>

namespace ugb {

    class Food : public Entity {
        public:
            Food(bn::fixed_point spawn_position);
            void update() override;

        private:
        bn::sprite_animate_action<6> _animation;
    };
}