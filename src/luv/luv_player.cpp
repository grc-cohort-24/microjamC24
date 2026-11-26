#include "luv/luv_player.h"

#include <bn_keypad.h>
#include "bn_sprite_items_luv_fish.h"

namespace luv
{
    /**
     * player constructor
     */
    luv_player::luv_player(bn::fixed_point starting_position, bn::fixed speed) 
    : _sprite(bn::sprite_items::luv_fish.create_sprite(starting_position)),
        _sprite_action(bn::create_sprite_animate_action_forever(
            _sprite, 
            10, 
            bn::sprite_items::luv_fish.tiles_item(), 
            0, 1, 2, 3)),
        _speed(speed),
        _size({16, 16}),
        _bounding_box(generate_bounding_box(_sprite, _size))
    {
    }

    void luv_player::update()
    {
        _update_position();
        
        if (bn::keypad::any_held())
        {
            _update_animation();
        }

        //X-axis scroll logic
        if (_sprite.x() > MAX_X) {
            _sprite.set_x(MIN_X);
        }
        if (_sprite.x() < MIN_X) {
            _sprite.set_x(MAX_X);
        }

        //Y-axis scroll logic
        if (_sprite.y() > MAX_Y) {
            _sprite.set_y(MIN_Y);
        }
        if (_sprite.y() < MIN_Y) {
            _sprite.set_y(MAX_Y);
        }
    }

    // Get the player bounding box
    bn::rect luv_player::get_bounding_box()
    {
        return _bounding_box;
    };

    // Set the player bounding box
    void luv_player::set_bounding_box(bn::sprite_ptr _player_sprite, bn::size _player_size)
    {
        _bounding_box = generate_bounding_box(_player_sprite, _player_size);
    };

    //Set the player speed
    void luv_player::set_speed(bn::fixed _player_speed) {
        _speed = _player_speed;
    };

    /**
     * reads dpad movement
     */
    void luv::luv_player::_update_position()
    {
        if (bn::keypad::left_held())
        {
            _sprite.set_x(_sprite.x() - _speed);
        }
        if (bn::keypad::right_held())
        {
            _sprite.set_x(_sprite.x() + _speed);
        }
        if (bn::keypad::up_held())
        {
            _sprite.set_y(_sprite.y() - _speed);
        }
        if (bn::keypad::down_held())
        {
            _sprite.set_y(_sprite.y() + _speed);
            
        }

        //Update the bounding box
        set_bounding_box(_sprite, _size);
    }

    /**
     * reads the player dpad movement and updates the sprite animation.
     */
    void luv::luv_player::_update_animation()
    {
        
        if (bn::keypad::left_held())
        {
            _sprite.set_horizontal_flip(true);
            _sprite_action.update();
        }
        else  if (bn::keypad::right_held())
        {
            _sprite.set_horizontal_flip(false);
            _sprite_action.update();
        } else {
            _sprite_action.update();
        }
    }

    bn::fixed luv::luv_player::get_player_x() {
        return _sprite.x();
    };

    bn::fixed luv::luv_player::get_player_y() {
        return _sprite.y();
    };

}