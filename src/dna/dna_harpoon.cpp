#include "dna_harpoon.h"

#include "dna_hitbox.h"

#include "bn_sprite_items_dna_dot.h"

namespace dna {
    Harpoon::Harpoon(bn::fixed_point starting_pos, bn::fixed speed, bn::size size) :
    _sprite(bn::sprite_items::dna_dot.create_sprite(starting_pos)), 
    _speed(speed), 
    _hitbox(create_hitbox(_sprite, size)), 
    _size(size) {}

    void Harpoon::update() {
        _sprite.set_x(_sprite.x() + _speed);
        _hitbox = create_hitbox(_sprite, _size);
    }

    bool Harpoon::is_offscreen() const {
        return _sprite.x() > MAX_X + _size.width(); 
    }

    bn::rect Harpoon::getHitbox() const {
        return _hitbox; 
    }
}