#include "bn_sprite_items_food.h"
#include "ugb/ugb_food.h"

namespace ugb {

    Food::Food(bn::fixed spawn_x, bn::fixed spawn_y) : Entity::Entity(bn::sprite_items::food, spawn_x, spawn_y, 0) {};

    void Food::update() {
        Entity::update();
    }

}