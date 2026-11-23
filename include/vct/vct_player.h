#pragma once

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>

#include <bn_vector.h>
#include "mj_core.h"

namespace vct {

class player {
        //Screen bounds
        static constexpr int MAX_X = bn::display::width() / 2;
        static constexpr int MIN_X = -bn::display::width() / 2;
        static constexpr int MAX_Y = bn::display::height() / 2;
        static constexpr int MIN_Y = -bn::display::height() / 2;

    public:
        //Player constructor
        player(bn::fixed_point starting_position, int difficulty);
        
        //Constantly updates the game
        void update(bn::random& random);

        //Reutnr when the quick time event is successfully comepleted (for ending the game)
        //I realized that we need a win condition since there isn't one by defualt
        bool qte_complete() const;
    
    private:
        //Player sprite
        bn::sprite_ptr _sprite;
        
        //Where the integers value for the buttons are stored, and the max that are able to be stored
        int _max[3];   

        //Max amount of buttons ON SCREEN
        int _buttons = 3;
        
        //Roughly how many buttons needed to be pressed for this round (scaled based on difficulty)
        int _level;

        //The length that the fish sprite will be reeled up on the screen
        int _reel;

        //The amount of currently correctly pressed keys
        int _pressed = 0;        
        
        //Whether the game has started ()
        bool _started = false;   
                         
        //The vector that contains the text sprits on screen
        bn::vector<bn::sprite_ptr, 16> _words;  

        //This handles the player input for the QTE
        void qte(bn::random& random);
        //This handles the games actual QTE event
        void sequence(bn::random& random);
};

}