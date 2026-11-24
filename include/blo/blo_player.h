#pragma once

#include "blo_shark.h"

namespace blo
{
    class player
    {
    public:
        /**
         * player constructor
         */
        player(bn::fixed_point starting_position);

        void update(shark &shark);

    private:
        bn::sprite_ptr _sprite;
    };

}
