#include "nsj_Enemy.h"
#include "nsj_player.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_items_nsj_fish.h"
#include "bn_sprite_items_nsj_hook.h"
#include <bn_keypad.h>
#include "nsj_boundingBox.h"
#include "bn_rect.h"
namespace nsj
{
    static constexpr bn::size ENEMY_SIZE = {8, 8};
    constexpr int ENEMY_ANIMATION_SPEED = 10;

    Enemy::Enemy(bn::fixed x_start, bn::fixed y_start, bn::fixed x_speed, bn::fixed y_speed, bn::random &rng) : _sprite(bn::sprite_items::nsj_hook.create_sprite(x_start, y_start)), _sprite_action(bn::create_sprite_animate_action_forever(
                                                                                                                                                                    _sprite,
                                                                                                                                                                    ENEMY_ANIMATION_SPEED,
                                                                                                                                                                    bn::sprite_items::nsj_hook.tiles_item(),
                                                                                                                                                                    0, 1, 2)),
                                                                                                                                                                     _x_speed(x_speed), _y_speed(y_speed),
                                                                                                                                                                    _size(ENEMY_SIZE),
                                                                                                                                                                    _rng(rng)
    {
        if(_rng.get_int(2)==0){
            _y_speed = -y_speed;
        }
        _bounding_box = create_bounding_box(_sprite, _size);
    }

    bn::rect nsj::Enemy::get_bounding_box()
    {
        return _bounding_box;
    }

    void Enemy::update()
    {

        _sprite.set_x(_sprite.x() + _x_speed);
        _sprite.set_y(_sprite.y()+ _y_speed);

        if (_sprite.x() >= MAX_X)
        {
            _sprite.set_x(MIN_X);
            _sprite.set_y(_rng.get_int(-60, 40));
        }

        else if (_sprite.x() <= MIN_X)
        {
            _sprite.set_x(MAX_X);
            _sprite.set_y(_rng.get_int(-60, 40));
        }
          _sprite_action.update();
        _bounding_box = create_bounding_box(_sprite, _size);
    }
}
