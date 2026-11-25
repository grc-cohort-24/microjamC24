#include <bn_core.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_animate_actions.h>

#include "bn_sprite_items_bnc_bubble.h"

#include "bnc/bnc_bubbles.h"
#include "bnc/bnc_squid.h"
#include "bnc/bnc_whale.h"
#include "bnc/bnc_squid_escape.h"
#include "mj/mj_game_data.h"


namespace bnc {

    //bubble constructor
    Bubbles::Bubbles(bn::fixed bubble_x, bn::fixed bubble_y, bn::fixed bubble_speed) :
    _bubble(bn::sprite_items::bnc_bubble.create_sprite(bubble_x, bubble_y)),
    _bubble_speed(bubble_speed)
    {}

    void Bubbles::update(){
        _bubble.set_y(_bubble.y() - _bubble_speed);

        if(_bubble.y() < MIN_Y){
            _bubble.set_y(MAX_Y);
        }
    }


    

    // bn::sprite_ptr _bubble_animation = bn::sprite_items::bnc_bubble.create_sprite();
    // _bubble_animation.set_tiles(bn::sprite_items::bnc_bubble.tiles_item(), 3);

    // bn::sprite_animate_action<12> animation = bn::create_sprite_animate_action_forever(
    //         _bubble_animation,
    //             10, 
    //             bn::sprite_items::bnc_bubble.tiles_item(),
    //         0,1,2,3,4,5,6,5,4,3,2,1
    //     );
    }
