#pragma once

#include "ugb/ugb_entity.h"

namespace ugb {

    class Hook : public Entity {
        public:
            Hook(bn::fixed spawn_x, bn::fixed spawn_y);

            void update() override;
    };
}