#include "vct_player.h"
#include <bn_keypad.h>
#include "bn_sprite_items_vct_angler.h"
#include "bn_sprite_items_vct_a.h"
#include "bn_sprite_items_vct_b.h"
#include "bn_sprite_items_vct_l.h"
#include "bn_sprite_items_vct_r.h"

namespace vct {

//Basic player constructor, all inital values go here
player::player(bn ::fixed_point starting_position, int difficulty) :
    _sprite(bn::sprite_items::vct_angler.create_sprite(starting_position)),
    _level(difficulty)
{}

//Updates the player on screen
void player::update(bn::random& random) {
    qte(random);
}

//Win condition
bool player::qte_complete() const
{
    return _sprite.y() < MIN_Y; //remember the inverse y axis
}

//This handles the games actual QTE event
void player::sequence(bn::random& random)
{
    _words.clear(); //Words MUST be cleared
    _pressed = 0; //Initializes the start of the game with 0 currently pressed buttons


    //Max_X - Min_X = screen length. (Spaced out evenly across the screen in 4 sections)
    int spacing = (MAX_X - MIN_X) / 4;
    int x = MIN_X + spacing;

    //Returns the distance the fish is reeled (by a 8th of the screen)
    _reel = (MAX_Y - MIN_Y) / 8;

    for(int i = 0; i < _buttons; i++)
    {
        //Assigns index i of the max letters vector a random number, which then gets assigned
        //as a button
        _max[i] = random.get_int(4);

        if (_max[i] == 0)
        {
            _words.push_back(bn::sprite_items::vct_a.create_sprite(x, 50));
        }
        else if (_max[i] == 1)
        {
            _words.push_back(bn::sprite_items::vct_b.create_sprite(x, 50));
        }
        else if (_max[i] == 2)
        {
            _words.push_back(bn::sprite_items::vct_l.create_sprite(x, 50));
        }
        else if (_max[i] == 3)
        {
            _words.push_back(bn::sprite_items::vct_r.create_sprite(x, 50));
        }

        x += spacing; //For each iteration of the for loop, the next word will move another 1/_length of the screen over
    }
}

//This handles the player input for the QTE
void player::qte(bn::random& random) {

    //This if block is REQUIRED. Bool checks game started, if not, toggles true
    //and blocks the game from being able to be ran WHILE the game is currently running.
    if(!_started)
    {
        sequence(random);
        _started = true;
    }

    _sprite.set_y(_sprite.y() + (bn::fixed(_level)/60));//Makes the fish sink based on difficulty
                                                        //(After countless tests, 60 was the perfect number
                                                        //to stabilize difficulty)

    //Prevents the fish from leaving frame if the player is too slow
    if(_sprite.y() > MAX_Y)
    {
        _sprite.set_y(MAX_Y);
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

    //After passing a QTE, moves onto the next and highlights that sprite (moves onto next sprite frame)
    if (pressed != -1)
    {
        _sprite.set_y(_sprite.y() - _reel);//Reels the fish up one chunk (Note, Butanos Y axis is flipped)
        _pressed++;

        //After all 3 buttons are pressed, spawn a new batch
        if (_pressed == _buttons)
        {
            sequence(random);   //If the player gets 3 presses correct, 
                                                //gives a new batch of letters to press
        }

        //As long as there are still buttons to be pressed, this else statement always runs
        else
        {
            //Goes through all 3 buttons and only the current one gets frame 1
            for(int i = 0; i < 3; i++)
            {
                int frame = 0;

                if(i == _pressed)
                {
                    frame = 1;
                }


                if (_max[i] == 0)
                {
                    _words[i].set_tiles(bn::sprite_items::vct_a.tiles_item(), frame);
                }
                else if (_max[i] == 1)
                {
                    _words[i].set_tiles(bn::sprite_items::vct_b.tiles_item(), frame);
                }
                else if (_max[i] == 2)
                {
                    _words[i].set_tiles(bn::sprite_items::vct_l.tiles_item(), frame);
                }
                else if (_max[i] == 3)
                {
                    _words[i].set_tiles(bn::sprite_items::vct_r.tiles_item(), frame);
                }
            }
        }
    }
}
}