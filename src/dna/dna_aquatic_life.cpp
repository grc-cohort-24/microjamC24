#include "bn_sprite_items_dna_dot.h"

#include "dna_player.h"
#include "dna_aquatic_life.h"
#include "dna_hitbox.h"

#include "bn_sprite_items_dna_shark.h"
#include "bn_sprite_items_dna_squid.h"

namespace {



}
            
namespace dna {

    static constexpr int SPAWN_OFFSET = 5;

    AquaticLife::AquaticLife(bn::random &random, bn::fixed speed, bn::size size) :
    _sprite(Enemy(random)), 
    _speed(speed), 
    _hitbox(create_hitbox(_sprite, size)), 
    _size(size) {}


    bn::sprite_ptr AquaticLife::Enemy (bn::random &random) {
        int random_val = random.get_int(0, 2); 

        if (random_val == 1) {
            return bn::sprite_items::dna_squid.create_sprite(getStartPosition(random));
        } else {
            return bn::sprite_items::dna_shark.create_sprite(getStartPosition(random));
        }
    }

    bn::fixed_point AquaticLife::getStartPosition(bn::random &random) {
        bn::fixed randY = random.get_fixed(MIN_Y + SPAWN_OFFSET, MAX_Y - SPAWN_OFFSET); 
        bn::fixed startX = MAX_X - SPAWN_OFFSET; 

        return bn::fixed_point(startX, randY); 
    
    }

    bool AquaticLife::update(Player &player) {
        _sprite.set_x(_sprite.x() - _speed); 

        _hitbox = create_hitbox(_sprite, _size); 

        return _hitbox.intersects(player.getHitbox()); 
    }

    bool AquaticLife::is_offscreen() const {
        return _sprite.x() < MIN_X - _size.width();
    }

    bn::rect AquaticLife::getHitbox() const {
        return _hitbox;
    }
}