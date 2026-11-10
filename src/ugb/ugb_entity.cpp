#include <bn_sprite_item.h>

#include "ugb/ugb_common.h"
#include "ugb/ugb_entity.h"

namespace ugb
{

    entity::entity(bn::sprite_item sprite_item, bn::fixed starting_x, bn::fixed starting_y, bn::fixed starting_speed) : _sprite(sprite_item.create_sprite(starting_x, starting_y)), _speed(starting_speed)
    {
        _bounding_box = create_bounding_box(_sprite, _sprite.dimensions());
    }

    entity::entity(bn::sprite_item sprite_item, bn::fixed starting_x, bn::fixed starting_y, bn::size starting_size, bn::fixed starting_speed) : _sprite(sprite_item.create_sprite(starting_x, starting_y)), _speed(starting_speed)
    {
        _bounding_box = create_bounding_box(_sprite, starting_size);
    }

    entity::entity(bn::sprite_item sprite_item, bn::fixed_point starting_position, bn::fixed starting_speed) : entity(sprite_item, starting_position.x(), starting_position.y(), starting_speed) {};

    void entity::update()
    {
        _bounding_box = create_bounding_box(_sprite, _sprite.dimensions());
    }

    bn::fixed entity::x() const
    {
        return _sprite.x();
    }

    bn::fixed entity::y() const
    {
        return _sprite.y();
    }

    bn::rect entity::bounding_box() const
    {
        return _bounding_box;
    }

}