#include "bar_bouncer.h"

namespace bar
{
    bar_bouncer::bar_bouncer(bn::fixed x_start, bn::fixed y_start, bn::fixed base_speed, bn::size bouncer_size) : _sprite(bn::sprite_items::bar_bouncer.create_sprite(x_start, y_start)),
                                                                                                                  _horizontal_speed(base_speed), _size(bouncer_size),
                                                                                                                  _bounding_box(bar_create_bounding_box(_sprite, bouncer_size)), _is_hit(false), _is_collided(false)
    {
    }

    void bar_bouncer::update()
    {
        bn::fixed y = _sprite.y();

        _is_collided = false;

        if (!_is_hit)
        {
            y += _horizontal_speed;
        }
        else
        {
            y -= _horizontal_speed;
        }

        if (y <= MIN_Y)
        {
            _is_hit = false;
        }

        _sprite.set_y(y);

        _bounding_box = bar_create_bounding_box(_sprite, _size);
    }
}