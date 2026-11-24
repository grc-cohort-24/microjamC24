#include "gam_ship.h"
#include "bn_sprite_items_gam_ship.h"
#include "gam_grid_layout.h"

namespace gam {

    /**
     * Creates ship with input size, orientation and coords
     * @param size how many gridd squares the ship occupies
     * @param horizontal true if the ship is horizontal
     * @param start_x the first x coordinate of this ship
     * @param start_y the first y coordinate of this ship
    */
    gam_ship::gam_ship(int size, bool horizontal, int start_x, int start_y) :
    _ship_horizontal(horizontal) {
        if(size > MAX_SIZE) {
            _ship_size = MAX_SIZE;
        }
        else {
            _ship_size = size;
        }

        if(horizontal) {
            for(int i = 0; i < _ship_size; i++) {
                _ship_x_coords.push_back(start_x + i);

                _ship_sprites.push_back(bn::sprite_items::gam_ship.create_sprite(
                  First_Square_X + (start_x + i) * Square_Size, First_Square_Y + start_y * Square_Size));
            }
            _ship_y_coords.push_back(start_y);
        }
        else {
            for(int i = 0; i < _ship_size; i++) {
                _ship_y_coords.push_back(start_y + i);

                _ship_sprites.push_back(bn::sprite_items::gam_ship.create_sprite(
                    First_Square_X + start_x * Square_Size, First_Square_Y + (start_y + i) * Square_Size));
            }
            _ship_x_coords.push_back(start_x);
        }

        // Start every square hidden so the board does not reveal ship locations.
        for (bn::sprite_ptr& sprite : _ship_sprites)
        {
            sprite.set_visible(false);
        }

    }
    
    /**
     * @return the number of grid squares the ship occupies
    */
    int gam_ship::size() {
        return _ship_size;
    }

    /**
     * @return true if the ship is horizontal. False if vertical
    */
    bool gam_ship::horizontal() {
        return _ship_horizontal;
    }

    /**
     * @return the x coords the ship is located at
    */
    bn::vector<int, MAX_SIZE> gam_ship::x_coords() {
        return _ship_x_coords;
    }
    
    /**
     * @return the y coords the ship is located at
    */
    bn::vector<int, MAX_SIZE> gam_ship::y_coords() {
        return _ship_y_coords;
    }
    
    /**
     * @return true if the ship has been hit. False if not
    */
    bool gam_ship::is_hit() const {
        return _ship_hit; 
    }

    bool gam_ship::try_to_hit(int column, int row) {
        if(_ship_hit) {
            return false;
        }

        for (int i = 0; i < _ship_size; i++) {

            int filled_column;
            int filled_row;

            if(_ship_horizontal) {
                // Row stays the same and column changes
                filled_column = _ship_x_coords[i]; 
                filled_row = _ship_y_coords[0];
            }
            else {
                // Column stays the same while row changes (vertical)
                filled_column = _ship_x_coords[0];
                filled_row = _ship_y_coords[i]; 
            }

            if(column == filled_column && row == filled_row) { // If the ship is hit ..
                // Ship is hit and is now sunk
                _ship_hit = true;

                // Start the animation process at the flash frame
                _frames_since_hit = 0;
                _show_ship_frame(_flash_sprite);

                return true; 
            }
        }

        return false; // Missed so return false
    }

    void gam_ship::update_visibility(int selected_column, int selected_row) {
        for (int i = 0; i < _ship_size; i++) {
            int ship_cell_column;
            int ship_cell_row;
        
            if(_ship_horizontal) {
                // Horizontal cells share a row and have different columns
                ship_cell_column = _ship_x_coords[i];
                ship_cell_row = _ship_y_coords[0];
            }
            else {
                // Vertical segments share a column and have different rows
                ship_cell_column = _ship_x_coords[0];
                ship_cell_row = _ship_y_coords[i];
            }
            
            bool isSelected = false;
            // Select this cell only when the column and row match the position of a ship
            if (ship_cell_column == selected_column && ship_cell_row == selected_row) {
                isSelected = true;
            }

            // Sunk ships always stay visible. Unsunk ships need to be selected to become visible
            if (_ship_hit || isSelected) {
                _ship_sprites[i].set_visible(true);
            }
            else {
                _ship_sprites[i].set_visible(false);
            }
        }
    }

    void gam_ship::_show_ship_frame(int frame_index) {
        for (bn::sprite_ptr& sprite : _ship_sprites) {
            // Change the frame that is visible
            sprite.set_tiles(bn::sprite_items::gam_ship.tiles_item(), frame_index);
            sprite.set_visible(true);
        }
    }

    bool gam_ship::animation_is_running() const {
        // Animation will only run after a ship is hit and will stop once 8 frames have passed
        if (_ship_hit && _frames_since_hit < _frames_per_animation * 3) { // * 3 because there is 3 animations to get through
            return true;
        }
        else {
            return false;
        }
    }

    void gam_ship::update_animation() {
        // Do not advance the animations while it is unsunk
        if (!animation_is_running()) {
            return;
        }

        _frames_since_hit++;

        if (_frames_since_hit == _frames_per_animation) {
            // Flash should show first then switch to fire after 8 frames
            _show_ship_frame(_fire_sprite);
        }
        else if (_frames_since_hit == _frames_per_animation * 2) {
            // Switch to wrecked ship image which will stay visible
            _show_ship_frame(_wreck_sprite);
        }
    }
}