#include "vct_player.h"
#include <bn_keypad.h>
#include "bn_sprite_items_vct_angler.h"
#include "bn_sound_items.h"

namespace vct {

//Basic player constructor, all inital values go here
player::player(bn ::fixed_point starting_position, bn::fixed speed) :
    _sprite(bn::sprite_items::vct_angler.create_sprite(starting_position)),
    _speed(speed)
{}

//Updates the player on screen
void player::update() {
    _update_position();
}

//Handles player movement (position on screen)
void player::_update_position() {
    if(bn::keypad::left_held()) {
        _sprite.set_x(_sprite.x() - _speed);
    }
    if(bn::keypad::right_held()) {
        _sprite.set_x(_sprite.x() + _speed);
    }
    if(bn::keypad::up_held()) {
        _sprite.set_y(_sprite.y() - _speed);
    }
    if(bn::keypad::down_held()) {
        _sprite.set_y(_sprite.y() + _speed);
    }
}

//Checks if the player moves out of bounds (wins or loses)
//And returns a true or false based on that
bool player::out_of_bounds() const {
    return _sprite.x() > MAX_X || _sprite.x() < MIN_X ||
           _sprite.y() > MAX_Y || _sprite.y() < MIN_Y;
}

}