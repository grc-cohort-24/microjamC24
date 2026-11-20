#include "bn_sprite_items_dna_dot.h"

#include "dna_player.h"
#include "dna_aquatic_life.h"
#include "dna_hitbox.h"
#include "bn_sprite_items_dna_shark.h"
            
namespace dna {

    AquaticLife::AquaticLife(bn::random &random, bn::fixed speed, bn::size size) :
    _sprite(bn::sprite_items::dna_shark.create_sprite(getStartPosition(random))), 
    _speed(speed), 
    _hitbox(create_hitbox(_sprite, size)), 
    _size(size) {}

    bn::fixed_point AquaticLife::getStartPosition(bn::random &random) {
        bn::fixed randY = random.get_fixed(MIN_Y + 5, MAX_Y - 5); 
        bn::fixed startX = MAX_X - 5; 

        return bn::fixed_point(startX, randY); 
    }

    bool AquaticLife::update(Player &player) {
        _sprite.set_x(_sprite.x() - _speed); 

        _hitbox = create_hitbox(_sprite, _size); 

        return _hitbox.intersects(player.get_hitbox()); 
    }

    bool AquaticLife::is_offscreen() const {
        return _sprite.x() < MIN_X - 8;
    }
}