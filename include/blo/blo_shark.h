#pragma once

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_item.h>

namespace blo
{
    class shark
    {
    public:
        /**
         * shark constructor
         *
         * @param starting_position the location of the shark
         * @param window the timing window
         * @param has_fakeout if the shark will fakeout
         */
        shark(bn::fixed_point starting_position, int window, bool has_fakeout);

        void update();

        // Hits the shark
        void bonk();

        // Checks to see if the shark has been hit
        bool bonked() const;

        // Checks to see if the shark stole the snack
        bool snack_stolen() const;

        // Checks to see if the shark is fully emerged (Ready to hit)
        bool isEmerged() const;

        // Checks to see if the shark is doing a fakeout
        bool isFakeout() const;

    private:
        bn::sprite_ptr _sprite;
        bn::sprite_ptr _half_emerged_sprite;
        bn::sprite_ptr _partially_emerged_sprite;
        int _emerge_start = 180;
        int _window;
        bool _has_fakeout;
        int _fakeout_start = 240;
        int _fakeout_length = 30;
        bool _snack_stolen = false;
        bool _bonked = false;
        int _frames = 0;
        int _emerge_stage = 0;
    };
}