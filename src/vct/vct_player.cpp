#include "vct_player.h"
#include <bn_keypad.h>
#include "bn_sprite_items_vct_angler.h"

namespace vct {

//Basic player constructor, all inital values go here
player::player(bn ::fixed_point starting_position, int difficulty) :
    _sprite(bn::sprite_items::vct_angler.create_sprite(starting_position)),
    _length(difficulty)
{}

//Updates the player on screen
void player::update(bn::random& random, const bn::sprite_text_generator& text_generator) {
    qte(random, text_generator);
}

//Win condition
bool player::qte_complete() const
{
    return _pressed >= _length;
}

//This handles the games actual QTE event
void player::sequence(bn::random& random, const bn::sprite_text_generator& text_generator)
{
    _words.clear(); //Words MUST be cleared
    _pressed = 0; //Initializes the start of the game with 0 currently pressed buttons


    //Max_X - Min_X = screen length.
    int spacing = (MAX_X - MIN_X) / 4;
    reel = (MAX_Y - MIN_Y) / _length;
    int x = MIN_X + spacing;

    for(int i = 0; i < _length; i++)
    {
        //Assigns index i of the max letters vector a random number, which then gets assigned
        //as a button
        _max[i] = random.get_int(4);

        if (_max[i] == 0)
        {
            text_generator.generate(x, 50, "A", _words);
        }
        else if (_max[i] == 1)
        {
            text_generator.generate(x, 50, "B", _words);
        }
        else if (_max[i] == 2)
        {
            text_generator.generate(x, 50, "L", _words);
        }
        else if (_max[i] == 3)
        {
            text_generator.generate(x, 50, "R", _words);
        }

        x += spacing; //For each iteration of the for loop, the next word will move another 1/_length of the screen over
    }
}

//This handles the player input for the QTE
void player::qte(bn::random& random, const bn::sprite_text_generator& text_generator) {
    
    //This if block is REQUIRED. The bool checks if the game started, if not it toggles to true
    //and blocks the game from being able to be ran WHILE the game is currently running.
    //This was a big issue when testing because the qte words would rapidly change since the game
    //started over and over again.
    if(!_started)
    {
        sequence(random, text_generator);
        _started = true;
    }

    //If the amount of pressed buttons meets the required amount, return to end early
    if(_pressed >= _length)
    {
        return;
    }

    int pressed = -1;   //-1 means nothing pressed (default value since 0 is a button)

    //QTE inputs
    if(bn::keypad::a_pressed())
    {
        pressed = 0;
    }
    else if(bn::keypad::b_pressed())
    {
        pressed = 1;
    }
    else if(bn::keypad::l_pressed())
    {
        pressed = 2;
    }
    else if(bn::keypad::r_pressed())
    {
        pressed = 3;
    }

    //After passing a QTE, hides the letter (WILL NEED TO BE CHANGED, THIS IS A PLACEHOLDER FEATURE)
    if (pressed != -1)
    {
        if (pressed == _max[_pressed])
        {
            _words[_pressed].set_visible(false);//Makes the pressed letter invisible, so the player knows they pressed the correct one
             _sprite.set_y(_sprite.y() - reel);//Reels the fish up one chunk (Note, Butanos Y axis is flipped)
            _pressed++;} 

            //After all 3 are pressed, spawn a new batch
        if (_pressed == 3)
        {
            sequence(random, text_generator);   //If the player gets 3 presses correct, 
                                                //gives a new batch of letters to press
        }
    }
}
}