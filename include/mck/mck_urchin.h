#pragma once

#include <bn_sprite_ptr.h>
#include <bn_rect.h>
#include <bn_sprite_animate_actions.h>

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

        void update();
    
    private:
        // The sprite to display the urchin
        bn::sprite_ptr _sprite;
        bn::sprite_animate_action<4> _animation;
    };
}