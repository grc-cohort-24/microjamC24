#pragma once

#include <bn_vector.h>

#include "ugb/ugb_constants.h"
#include "ugb/ugb_entity.h"
#include "ugb/ugb_hook.h"
#include "ugb/ugb_food.h"

namespace ugb {

    namespace state {
        // TODO: Revisit this, why does adding extern get this to compile??
        extern bn::vector<Entity, constants::MAX_ENTITIES> entities;
        extern bn::vector<Entity*, constants::MAX_ENTITIES> hooks;
        extern bn::vector<Entity*, constants::MAX_ENTITIES> food;
        extern bn::vector<bn::sprite_ptr, constants::MAX_SCORE_CHARS> score_sprites;

        extern int score;
        extern bool reset_already;
    }

}