#ifndef DNA_HITBOX_H
#define DNA_HITBOX_H

#include <bn_rect.h>
#include <bn_sprite_ptr.h>

namespace dna {
    bn::rect create_hitbox(bn::sprite_ptr sprite, bn::size box_size);
}

#endif