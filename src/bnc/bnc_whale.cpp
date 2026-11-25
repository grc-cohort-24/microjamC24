#include "bnc/bnc_whale.h"
#include "bnc/bnc_squid_escape.h"
#include "bn_sprite_items_bnc_whale.h"
#include "mj/mj_game_data.h"
#include "bnc/bnc_squid.h"

#include <bn_vector.h>
#include <bn_rect.h>
#include <bn_math.h>


namespace bnc{

    Whale::Whale(bn::fixed x, bn::fixed y, bn::fixed speed) :
    _whale(bn::sprite_items::bnc_whale.create_sprite(x, y)),
    _whale_hit_box(create_bounding_box(_whale, WHALE_SIZE)),
    _whale_speed(speed), _whale_size(WHALE_SIZE)
    {}

    //performs distance formula and returns distance between whale and squid
    bn::fixed Whale::distance_formula(bn::fixed whale_x, bn::fixed squid_x, bn::fixed whale_y, bn::fixed squid_y) {
        bn::fixed x_value = whale_x - squid_x;
        bn::fixed y_value = whale_y - squid_y;

        x_value *= x_value;
        y_value *= y_value;

        bn::fixed result = x_value + y_value;
        return bn::sqrt(result);
    }


    //Checks if squid collides with whale
    bool Whale::get_whale_collision() const {
        return _whale_collision;
    }

    //Checks if whales spawn too close to squid
    bool Whale::is_too_close(Squid& squid) {
        //if whale spawns less than 10 pixels away from squid,
        //return true
        if(distance_formula(_whale.x(), squid.get_position().x(), 
        _whale.y(), squid.get_position().y()) <= _distance_difference) {
            return true;
        } else {
            return false;
        }
    }

    //updates hit box and position of the whale continuously
    void Whale::update(Squid& squid) {
        if(_whale.x() < squid.get_position().x()){
            _whale.set_x(_whale.x() + _whale_speed);
        }

        if(_whale.x() > squid.get_position().x()){
            _whale.set_x(_whale.x() - _whale_speed);
        }

        if(_whale.y() > squid.get_position().y()){
            _whale.set_y(_whale.y() - _whale_speed);
        }

        if(_whale.y() < squid.get_position().y()){
            _whale.set_y(_whale.y() + _whale_speed);
        }

        _whale_hit_box = create_bounding_box(_whale, WHALE_SIZE);
        
        if(_whale_hit_box.intersects(squid.get_squid_hit_box())){
            _whale_collision = true;
        }
    }
}