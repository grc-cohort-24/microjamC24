#pragma once

#include <bn_sprite_ptr.h>
#include <bn_fixed.h>
#include <bn_size.h>
#include <bn_rect.h>
#include <bn_display.h>

namespace bnc {

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};

//Starting position of the player
static constexpr int X_START = -90;
static constexpr int Y_START = 0;

//Speed of the player
static constexpr bn::fixed SPEED = 1;

bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size);

class Minnow {

    static constexpr int MIN_Y = -bn::display::height() / 2;
    static constexpr int MAX_Y = bn::display::height() / 2;
    static constexpr int MIN_X = -bn::display::width() / 2;
    static constexpr int MAX_X = bn::display::width() / 2;

    public:

    // The sprite to display the player
    bn::sprite_ptr _sprite;

    //constructor
    Minnow(bn::fixed_point starting_position, bn::fixed speed);

    void update();

    // bn::rect minnow_hit_box();
      bn::rect minnow_hit_box;

    bool out_of_bounds() const;

    private:

  
    bn::fixed _speed;


    //direction number
    int direction;


    //if statemenst for the minnows direction goes here

    /**
     * Reads from the d-pad and moves the player by one frame accordingly.
     */
    void _update_position();

};
}