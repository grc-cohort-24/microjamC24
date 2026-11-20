#include "mck/mck_urchin.h"

#include "bn_sprite_items_mck_urchin.h"

namespace mck {

/**
    * Urchin constructor
    * 
    * @param urchin_spawn Sets the spawning point
*/
urchin::urchin(bn::fixed_point urchin_spawn) :
    _sprite(bn::sprite_items::mck_urchin.create_sprite(urchin_spawn))
    {}


bn::rect urchin::hitbox() const {
    return bn::rect(_sprite.x().integer(), _sprite.y().integer(), 16, 16);
}
}