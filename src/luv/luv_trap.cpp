#include "luv/luv_trap.h"
#include "bn_sprite_items_luv_trap.h"
#include "bn_sprite_items_luv_jellyfish.h"

namespace luv {
    /**
     * Trap Jellyfish constructor
     */
    luv_trap::luv_trap(bn::fixed_point spawn) : 
    _sprite(bn::sprite_items::luv_jellyfish.create_sprite(spawn)), _size({ANEMONE_SIZE,ANEMONE_SIZE}),
    _bounding_box(generate_bounding_box(_sprite, _size)),
    _sprite_action(bn::create_sprite_animate_action_forever(
        _sprite,
        8,
        bn::sprite_items::luv_jellyfish.tiles_item(),
        0, 1, 2, 3, 4, 5, 6, 7)) {

    }
    
    //Get the trap anemone bounding box
     bn::rect luv_trap::get_bounding_box() {
        return _bounding_box;
    };

    //Update the trap's current frame
    void luv::luv_trap::update_trap_animation() {
        _sprite_action.update();
    };

    // Move the jellyfish up
    void luv::luv_trap::float_up() {
        _sprite.set_y(_sprite.y() - 1.5);
        _sprite.set_vertical_flip(false);
        _bounding_box = generate_bounding_box(_sprite,_size);
    };

    // Move the jellyfish down
    void luv::luv_trap::float_down()
    {
        _sprite.set_y(_sprite.y() + 1.5);
        _sprite.set_vertical_flip(true);
        _bounding_box = generate_bounding_box(_sprite, _size);
    };
}