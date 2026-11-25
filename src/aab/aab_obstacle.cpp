#include "aab/aab_obstacle.h"
#include "bn_sprite_items_aab_log.h"
#include <bn_camera_ptr.h>

namespace aab
{
    Obstacle::Obstacle(bn::fixed_point starting_position) : 
        _sprite(bn::sprite_items::aab_log.create_sprite(starting_position))
    {
    }

    void Obstacle::update()
    {
        // You can leave it static or add movement here if desired
    }

    void Obstacle::set_camera(const bn::camera_ptr& camera){
        _sprite.set_camera(camera);
    }

    bn::fixed Obstacle::x() const{
        return _sprite.x();
    }

    bn::fixed Obstacle::y() const{
        return _sprite.y();
    }

}