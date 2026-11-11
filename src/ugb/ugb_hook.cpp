#include "bn_sprite_items_hook.h"

#include "ugb/ugb_hook.h"

namespace ugb {

    hook::hook(bn::fixed_point spawn_position) : entity::entity(bn::sprite_items::hook, spawn_position, 0) {};

    void hook::update() {
        entity::update();
    }
}