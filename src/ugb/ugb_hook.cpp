#include "bn_sprite_items_hook.h"

#include "ugb/ugb_hook.h"

namespace ugb {

    Hook::Hook(bn::fixed_point spawn_position) : Entity::Entity(bn::sprite_items::hook, spawn_position, 0) {};

    void Hook::update() {
        Entity::update();
    }
}