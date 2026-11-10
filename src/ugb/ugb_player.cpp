#include <bn_keypad.h>

#include "bn_sprite_items_fish1.h"
#include "bn_sprite_items_fish2.h"

#include "ugb/ugb_player.h"

namespace ugb
{

    player::player(bn::fixed_point start_position, bn::fixed speed) : entity::entity(bn::sprite_items::fish1, start_position, speed) {};

    void player::update()
    {
        entity::update(); // Update _bounding_box
        _update_position();
        _update_animation();
    }

    void player::_update_position()
    {

        // movement
        if (bn::keypad::left_held())
        {
            _sprite.set_x(_sprite.x() - _speed);
            _sprite.set_horizontal_flip(true);
        }
        if (bn::keypad::right_held())
        {
            _sprite.set_x(_sprite.x() + _speed);
            _sprite.set_horizontal_flip(false);
        }
        if (bn::keypad::up_held())
        {
            _sprite.set_y(_sprite.y() - _speed);
        }
        if (bn::keypad::down_held())
        {
            _sprite.set_y(_sprite.y() + _speed);
        }
    }

    void player::_update_animation()
    {
        _animation_counter++;

        if (_animation_counter >= 10)
        {
            _is_fish2 = !_is_fish2; // flap the fin

            if (_is_fish2)
            {
                _sprite.set_item(bn::sprite_items::fish2);
            }
            else
            {
                _sprite.set_item(bn::sprite_items::fish1);
            }

            _animation_counter = 0;
        }
    }

}