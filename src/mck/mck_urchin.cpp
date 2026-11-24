#include "mck/mck_urchin.h"

#include "bn_sprite_items_mck_urchin.h"

namespace mck {

/**
    * Urchin constructor
    * 
    * @param urchin_spawn Sets the spawning point
*/
    urchin::urchin(bn::fixed_point urchin_spawn) :
        _sprite(bn::sprite_items::mck_urchin.create_sprite(urchin_spawn)),
        _animation(bn::create_sprite_animate_action_forever(_sprite, 8, bn::sprite_items::mck_urchin.tiles_item(),0,3))
        {}


    bn::rect urchin::hitbox() const {
        return bn::rect(_sprite.x().integer(), _sprite.y().integer(), 8, 8);
    }
    void urchin::update() {
        _animation.update();
    }
}