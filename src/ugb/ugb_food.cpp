#include "bn_sprite_items_food.h"
#include "ugb/ugb_food.h"

namespace ugb {

    food::food(bn::fixed spawn_x, bn::fixed spawn_y) : entity::entity(bn::sprite_items::food, spawn_x, spawn_y, 0) {};

    void food::update() {
        entity::update();
    }

}