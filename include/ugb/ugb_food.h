#pragma once

#include "ugb/ugb_entity.h"

namespace ugb {

    class food : public entity {
        public:
            food(bn::fixed spawn_x, bn::fixed spawn_y);

            void update();
    };
}