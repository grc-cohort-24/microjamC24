#include "nsj_player.h"
#include "bn_sprite_ptr.h"
#include "bn_fixed.h"
#include "bn_size.h"
#include "bn_rect.h"
#include "bn_sprite_animate_actions.h"

namespace nsj
{
    class Shark
    {
    private:
        bn::sprite_ptr _sprite;
        bn::sprite_animate_action<4> _sprite_action;
        bn::fixed _x_speed;
        bn::fixed _y_speed;
        bn::size _size;
        bn::rect _bounding_box;

    public:
        Shark(bn::fixed x_start, bn::fixed y_start, bn::fixed speed);

        void update(nsj::player &player);

        bn::rect get_bounding_box();
    };
}