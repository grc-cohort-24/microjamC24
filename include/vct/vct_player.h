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
        player(bn::fixed_point starting_position, int button_count);
        
        //Constantly updates the game
        void update(bn::random& random, const bn::sprite_text_generator& text_generator);

        //Reutnr when the quick time event is successfully comepleted (for ending the game)
        //I realized that we need a win condition since there isn't one by defualt
        bool qte_complete() const;
        
        //Returns true or false based on whether
        //the player has left the screen
        //bool out_of_bounds() const;
    
    private:
        //Player sprite
        bn::sprite_ptr _sprite;
        
        //The max amount of buttons needed to be pressed
        int _max[15];          

        //How many buttons needed to be pressed for this round
        int _length;

        //The amount of currently correctly pressed keys
        int _pressed = 0;        
        
        //Whether the game has started ()
        bool _started = false;   
                         
        //The vector that contains the text sprits on screen
        bn::vector<bn::sprite_ptr, 16> _words;  

        //adding sink timer so the fish sprite can sink every certain amount of frames
        int _sink_timer = 0;

        //removed static function, pretty sure it was mentioned we cannot use static in class
        const int reel_up_distance = 12;   //go up farther depending on your input
        const int penalty_distance = 16;   //get the input wrong and you go down farther
        const int sink_speed = 1;          //how fast the hook sinks down

        //This handles the player input for the QTE
        void qte(bn::random& random, const bn::sprite_text_generator& text_generator);
        //This handles the games actual QTE event
        void sequence(bn::random& random, const bn::sprite_text_generator& text_generator);
};

}