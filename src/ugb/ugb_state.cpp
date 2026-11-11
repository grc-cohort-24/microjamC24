#include "ugb/ugb_state.h"

namespace ugb {

    namespace state {
        bn::vector<Entity, constants::MAX_ENTITIES> entities;
        bn::vector<Entity*, constants::MAX_ENTITIES> hooks;
        bn::vector<Entity*, constants::MAX_ENTITIES> food;
        bn::vector<bn::sprite_ptr, constants::MAX_SCORE_CHARS> score_sprites;
        int score;
    }

}