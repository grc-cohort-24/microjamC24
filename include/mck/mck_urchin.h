#pragma once

#include <bn_sprite_ptr.h>
#include <bn_rect.h>

// All game functions/classes/variables/constants scoped to the namespace
namespace mck {
    class urchin {       
        
        public:
        
        /**
         * Urchin constructor
         * 
         * @param urchin_spawn Sets the spawning point
         */
        urchin(bn::fixed_point urchin_spawn);

        bn::rect hitbox() const;
    
    private:
        // The sprite to display the urchin
        bn::sprite_ptr _sprite;

    };
}