#include "bar_coin.h"

namespace bar
{
    bar_coin::bar_coin(bn::fixed x_start, bn::fixed y_start, bn::fixed base_speed, bn::size coin_size) : _sprite(bn::sprite_items::bar_coin.create_sprite(x_start, y_start)),
                                                                                                                  coin_animation(bn::create_sprite_animate_action_forever(_sprite, 10, bn::sprite_items::bar_coin.tiles_item(), 0, 1, 2, 1)),
                                                                                                                  _vertical_speed(base_speed), _size(coin_size),
                                                                                                                  _bounding_box(bar_create_bounding_box(_sprite, coin_size))
    {
    }

    void bar_coin::update()
    {
        _collided = false;
        _sprite.set_y(_sprite.y() + _vertical_speed);
        _bounding_box = bar_create_bounding_box(_sprite, _size);
        coin_animation.update();
    }

    bn::sprite_ptr bar_coin::get_sprite() const {
        return _sprite;
    }

    bn::rect bar_coin::get_bounding_box() const
    {
        return _bounding_box;
    }

    bool bar_coin::is_collided() const
    {
        return _collided;
    }

    void bar_coin::set_collided(bool set_status)
    {
        _collided = set_status;
    }
}