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
        player();

        void update(shark &target);
    };

}
