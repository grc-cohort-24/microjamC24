#pragma once

#include "ugb/ugb_entity.h"

namespace ugb {
    class hook : public entity {
        public:
            hook(bn::fixed_point spawn_position);

            void update();
    };
}