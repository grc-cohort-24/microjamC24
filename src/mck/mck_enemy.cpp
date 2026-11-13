#include "mck/mck_enemy.h"

#include <bn_keypad.h>

#include "bn_sprite_items_urchin.h"

#include "bn_sound_items.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace mck {

/**
 * enemy constructor
 * 
 * @param starting_position the location to start the enemy at
 * @param speed the pixels/frame the enemy moves at in each dimension
 */
enemy::enemy(bn::fixed_point starting_position, bn::fixed xspeed, bn::fixed yspeed) :
    _sprite(bn::sprite_items::urchin.create_sprite(starting_position)),
    x_speed(xspeed),
    y_speed(yspeed)
    {}


void enemy::update() {
    _update_position();
}

/**
 * Moves the enemy based on its current x and y speeds
 */
void mck::enemy::_update_position() {
    _sprite.set_x(_sprite.x() + x_speed);
    _sprite.set_y(_sprite.y() + y_speed);
}

bn::rect enemy::hitbox() const {
    return bn::rect(_sprite.x().integer(), _sprite.y().integer(), 16, 16);
}
}