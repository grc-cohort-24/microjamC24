#include "ugb/ugb_player.h"

#include <bn_keypad.h>
#include <bn_sprite_items_fish1.h>
#include <bn_sprite_items_fish2.h>

namespace ugb {

ugb_player::ugb_player(bn::fixed_point start_position, bn::fixed speed) :
    _sprite(bn::sprite_items::fish1.create_sprite(start_position)),
    _speed(speed)
{
}

void ugb_player::update() {

    _update_position();
    _update_animation();
}

void ugb_player::_update_position() {

    //movement
    if (bn::keypad::left_held()) {
        _sprite.set_x(_sprite.x() - _speed);
        _sprite.set_horizontal_flip(true);
    }
    if (bn::keypad::right_held()) {
        _sprite.set_x(_sprite.x() + _speed);
        _sprite.set_horizontal_flip(false);
    }
    if (bn::keypad::up_held()) {
        _sprite.set_y(_sprite.y() - _speed);
    }
    if (bn::keypad::down_held()) {
        _sprite.set_y(_sprite.y() + _speed);
    }
}

void ugb_player::_update_animation() {
    _animation_counter++;

    if (_animation_counter >= 10) {
        _is_fish2 = !_is_fish2; // flap the fin

        if (_is_fish2) {
            _sprite.set_item(bn::sprite_items::fish2);
        } else {
            _sprite.set_item(bn::sprite_items::fish1);
        }

        _animation_counter = 0;
    }
}

bn::fixed ugb_player::x() const {
    return _sprite.x();
}

bn::fixed ugb_player::y() const {
    return _sprite.y();
}

}