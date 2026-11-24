#include "blo/blo_player.h"
#include "blo/blo_shark.h"

#include <bn_keypad.h>

#include "bn_sprite_items_blo_player.h"

namespace blo
{
    /**
     * player constructor
     */
    player::player(bn::fixed_point starting_position) : _sprite(bn::sprite_items::blo_player.create_sprite(starting_position))
    {
    }

    void player::update(shark &shark)
    {
        if (bn::keypad::a_pressed())
        {
            shark.bonk();
        }
    }

}