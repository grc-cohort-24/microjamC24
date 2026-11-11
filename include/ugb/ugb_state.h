#pragma once

#include <bn_vector.h>

#include "ugb/ugb_constants.h"
#include "ugb/ugb_entity.h"

namespace ugb {

    namespace state {
        // TODO: Revisit this, why does adding extern get this to compile??
        extern bn::vector<Entity, constants::MAX_ENTITIES> entities;
        extern bn::vector<bn::sprite_ptr, constants::MAX_SCORE_CHARS> score_sprites;

        extern int score;
        extern int food_count;
    }

}