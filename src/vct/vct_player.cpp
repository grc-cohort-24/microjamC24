#include "vct_player.h"
#include <bn_keypad.h>
#include "bn_sprite_items_vct_angler.h"

namespace vct {

player::player(bn ::fixed_point starting_position, bn::fixed speed) :
    _sprite(bn::sprite_items::vct_angler.create_sprite(starting_position)),
    _speed(speed)
{}

void player::update() {
    _update_position();
}

//add player input below for movement 

bool player::out_of_bounds() const {
    return _sprite.x() > MAX_X || _sprite.x() < MIN_X ||
           _sprite.y() > MAX_Y || _sprite.y() < MIN_Y;
}

}