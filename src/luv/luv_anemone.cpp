#include "luv/luv_anemone.h"
#include "bn_sprite_items_luv_anemone.h"

namespace luv {
    
    luv_anemone::luv_anemone(bn::fixed_point spawn) : 
        _sprite(bn::sprite_items::luv_anemone.create_sprite(spawn)), _size({16, 16}),
        _bounding_box(generate_bounding_box(_sprite, _size)),
        _sprite_action(bn::create_sprite_animate_action_forever(
        _sprite, 
        10, 
        bn::sprite_items::luv_anemone.tiles_item(), 
        0, 1, 2))
    {

    }
    
    //Get the anemone bounding box
     bn::rect luv_anemone::get_bounding_box() {
        return _bounding_box;
    };

    void luv::luv_anemone::_update_animation()
    {
        _sprite_action.update();
    }
}