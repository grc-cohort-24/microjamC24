#include "bn_sprite_items_ugb_food.h"

#include "ugb/ugb_food.h"

namespace ugb {

    Food::Food(bn::fixed_point spawn_position) : 
        Entity::Entity(bn::sprite_items::ugb_food, spawn_position, 0),
        _animation(bn::create_sprite_animate_action_forever(
            _sprite,
            10,
            _tiles,
            0, 1, 2, 3, 2, 1))
            {};

    void Food::update() {
        Entity::update();
        _animation.update();
    }
}