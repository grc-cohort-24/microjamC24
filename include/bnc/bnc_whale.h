#pragma once

#include "bnc/bnc_squid.h"
#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_animate_actions.h>
#include <bn_display.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_fixed.h>
#include <bn_vector.h>

namespace bnc {
    // Width and height of the the player bounding box
    static constexpr bn::size WHALE_SIZE = {8, 8};

    //Speed and Max number of Whale that can spawn in the game;
    static constexpr bn::fixed WHALE_SPEED = 0.5;

    bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size);

    class Whale {
        public:
        //constructor
        Whale(bn::fixed x, bn::fixed y, bn::fixed speed);
    
        //getter functions
        void update(Squid& squid);
        bool get_whale_collision() const;
        bool is_too_close(Squid& squid); //returns true if whale spawns too close to squid
        
        //returns distance between squid and whale
        bn::fixed distance_formula(bn::fixed x1, bn::fixed x2, bn::fixed y1, bn::fixed y2); 

        private:
        bool _whale_collision = false;
        bn::fixed _distance_difference = 30; //Measures difference of x, y points between squid and whale
        bn::sprite_ptr _whale;
        bn::rect _whale_hit_box;
        bn::fixed _whale_speed;
        bn::size _whale_size;
    };
}