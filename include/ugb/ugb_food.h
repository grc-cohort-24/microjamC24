#pragma once

#include "ugb/ugb_entity.h"

namespace ugb {

    class Food : public Entity {
        public:
            Food(bn::fixed spawn_x, bn::fixed spawn_y);

            void update();
    };
}