#pragma once

#include <bn_display.h>
#include <bn_rect.h>
#include <bn_sprite_ptr.h>


namespace dna {
    static constexpr bn::size HARPOON_SIZE = {8, 8};
    static constexpr bn::fixed HARPOON_SPEED = 5;

    class Harpoon {
        static constexpr int MAX_X = bn::display::width() / 2;
        static constexpr int MIN_X = - bn::display::width() / 2;
        static constexpr int MAX_Y = bn::display::height() / 2;
        static constexpr int MIN_Y = - bn::display::height() / 2;

        public: 
            Harpoon(bn::fixed_point starting_pos, bn::fixed speed, bn::size size);

            bool is_offscreen() const;
            void update(); 

            bn::rect getHitbox() const; 
        private: 
            bn::sprite_ptr _sprite; 
            bn::fixed _speed; 
            bn::rect _hitbox; 
            bn::size _size; 
    };
}