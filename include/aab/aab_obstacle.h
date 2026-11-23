#pragma once

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>

namespace aab
{
    class Obstacle
    {
        public:
        Obstacle(bn::fixed_point starting_position);
        void update();
        void set_camera(const bn::camera_ptr& camera);
        bn::fixed x() const;
        bn::fixed y() const;

        private:
        bn::sprite_ptr _sprite;
    };
}