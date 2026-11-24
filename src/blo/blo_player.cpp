#include "blo/blo_player.h"
#include "blo/blo_shark.h"

#include <bn_keypad.h>

namespace blo
{
    /**
     * player constructor
     */
    player::player()
    {
    }

    void player::update(shark &target)
    {
        if (bn::keypad::a_pressed())
        {
            target.bonk();
        }
    }

}