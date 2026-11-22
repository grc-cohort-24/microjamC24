#include <bn_keypad.h>

#include "bn_sprite_items_ugb_fish.h"

#include "ugb/ugb_constants.h"
#include "ugb/ugb_player.h"

namespace ugb
{

    Player::Player(bn::fixed start_x, bn::fixed start_y, bn::fixed speed) :
        Entity::Entity(bn::sprite_items::ugb_fish, start_x, start_y, speed),
        _animation(bn::create_sprite_animate_action_forever(_sprite, constants::player::ANIMATION_WAIT_FRAMES, _tiles, 0, 1)){};

    void Player::update()
    {
        Entity::update(); // Update _bounding_box
        _update_position();
        _update_animation();
    }

    void Player::_update_position()
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

    void Player::_update_animation() {
        _animation.update();
    }

}