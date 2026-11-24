#include "mck/mck_enemy.h"

#include <bn_keypad.h>
#include <bn_sprite_animate_actions.h>

#include "bn_sprite_items_mck_shark.h"

#include "bn_sound_items.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace mck {

/**
 * enemy constructor
 * 
 * @param speed the pixels/frame the enemy moves at in each dimension
 * @param data the current game data, used for random number generation
 */
enemy::enemy(bn::fixed speed, bn::random& random) :
    // default values for instance variables; overwritten later
    _sprite(bn::sprite_items::mck_shark.create_sprite(bn::fixed_point(0, 0))),
    _xspeed(0),
    _yspeed(0),
    _animation(bn::create_sprite_animate_action_forever(_sprite, 8, bn::sprite_items::mck_shark.tiles_item(),0,1))
    {
        // determine a random side for the shark to spawn on
        int side = random.get_unbiased_int(NUM_SIDES);
        switch (side)
        {
            case 0 : // top
                _sprite = (bn::sprite_items::mck_shark.create_sprite
                    (bn::fixed_point(random.get_unbiased_int(MIN_X, MAX_X + 1), MIN_Y - SPAWN_MARGIN)));
                _xspeed = 0;
                _yspeed = speed;
                _animation = bn::create_sprite_animate_action_forever(_sprite, 8, bn::sprite_items::mck_shark.tiles_item(),6,7,8);
                break;
            case 1 : // right
                _sprite = (bn::sprite_items::mck_shark.create_sprite
                    (bn::fixed_point(MAX_X + SPAWN_MARGIN, random.get_unbiased_int(MIN_Y, MAX_Y + 1))));
                _xspeed = speed * -1;
                _yspeed = 0;
                _animation = bn::create_sprite_animate_action_forever(_sprite, 8, bn::sprite_items::mck_shark.tiles_item(),0,1,2);
                break;
            case 2 : // bottom
                _sprite = (bn::sprite_items::mck_shark.create_sprite
                    (bn::fixed_point(random.get_unbiased_int(MIN_X, MAX_X + 1), MAX_Y + SPAWN_MARGIN)));
                _xspeed = 0;
                _yspeed = speed * -1;
                _animation = bn::create_sprite_animate_action_forever(_sprite, 8, bn::sprite_items::mck_shark.tiles_item(),9,10,11);
                break;
            case 3 : // left
                _sprite = (bn::sprite_items::mck_shark.create_sprite
                    (bn::fixed_point(MIN_X - SPAWN_MARGIN, random.get_unbiased_int(MIN_Y, MAX_Y + 1))));
                _xspeed = speed;
                _yspeed = 0;
                _animation = bn::create_sprite_animate_action_forever(_sprite, 8, bn::sprite_items::mck_shark.tiles_item(),3,4,5);
                break;
            default :
                break;
        }
    }

void enemy::update() {
    _update_position();
    _animation.update();
}

/**
 * Moves the enemy based on its current x and y speeds
 */
void mck::enemy::_update_position() {
    _sprite.set_x(_sprite.x() + _xspeed);
    _sprite.set_y(_sprite.y() + _yspeed);
}

bn::rect enemy::hitbox() const {
    return bn::rect(_sprite.x().integer(), _sprite.y().integer(), 8, 8);
}
}