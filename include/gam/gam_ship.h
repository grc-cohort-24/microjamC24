#pragma once
#include <bn_vector.h>
#include "bn_sprite_ptr.h"

namespace gam {

    const int MAX_SIZE = 4;

    class gam_ship {
        public:

            /** 
             * Creates a new ship
             * @param size how many squares of the grid wide or tall the ship is
             * @param horizontal true if the ship is horizontal otherwise false
             * @param start_x the first x coordinate of this ship
             * @param start_y the first y coordinate of this ship
            */
            gam_ship(int size, bool horizontal, int start_x, int start_y);

            /**
             * Reveal only the selected square of an unsunk ship. Sunk ships are always visible
             * @param selected_column column currently selected by the player
             * @param selected_row row currently selected by the player
            */
            void update_visibility(int selected_column, int selected_row);

            /**
             * Returns true if this ship is sunk/hit
            */
            bool is_hit() const;

            bool try_to_hit(int column, int row);

            /**
             * @param size number of grid areas ship occupies
            */
            int size();

            /**
             * @return true if the ship is horizontal
            */
            bool horizontal();

            /**
             * @return x coordinates of this ship
            */
            bn::vector<int, MAX_SIZE> x_coords();

            /**
             * @return y coordinates of this ship
            */
            bn::vector<int, MAX_SIZE> y_coords();

            // Move the animation forward by one frame
            void update_animation();

            // Store whether the animation is running/playing
            bool animation_is_running() const;

        private:
          int _ship_size;
          bool _ship_horizontal;
          bool _ship_hit = false;
          bn::vector<int, MAX_SIZE> _ship_x_coords;
          bn::vector<int, MAX_SIZE> _ship_y_coords;
          bn::vector<bn::sprite_ptr, MAX_SIZE> _ship_sprites;
          
          static constexpr int _flash_sprite = 1;
          static constexpr int _fire_sprite = 2;
          static constexpr int _wreck_sprite = 3;

          // Hold each animation for 8 frames
          static constexpr int _frames_per_animation = 8;

          // Frames since this ship was hit
          int _frames_since_hit = 0;

          // Show one animation frame on each part of the ship
          void _show_ship_frame(int frame_index);
    };
}