#include "gam_ship.h"
#include "bn_sprite_items_ship.h"

namespace gam {

    /**
     * Creates ship with input size, orientation and coords
     * @param size how many gridd squares the ship occupies
     * @param horizontal true if the ship is horizontal
     * @param start_x the first x coordinate of this ship
     * @param start_y the first y coordinate of this ship
    */
    gam_ship::gam_ship(int size, bool horizontal, int start_x, int start_y) :
    ship_horizontal(horizontal) {
        if(size > MAX_SIZE) {
            ship_size = MAX_SIZE;
        }
        else {
            ship_size = size;
        }

        if(horizontal) {
            for(int i = 0; i < ship_size; i++) {
                ship_x_coords.push_back(start_x + i);

                ship_sprites.push_back(bn::sprite_items::ship.create_sprite(
                  -48 + (start_x + i) * 24,
                  -48 + start_y * 24));
            }
            ship_y_coords.push_back(start_y);
        }
        else {
            for(int i = 0; i < ship_size; i++) {
                ship_y_coords.push_back(start_y + i);

                ship_sprites.push_back(bn::sprite_items::ship.create_sprite(
                    -48 + start_x * 24, 
                    -48 + (start_y + i) * 24));
            }
            ship_x_coords.push_back(start_x);
        }



    }
    
    /**
     * @return the number of grid squares the ship occupies
    */
    int gam_ship::size() {
        return ship_size;
    }

    /**
     * @return true if the ship is horizontal. False if vertical
    */
    bool gam_ship::horizontal() {
        return ship_horizontal;
    }

    /**
     * @return the x coords the ship is located at
    */
    bn::vector<int, MAX_SIZE> gam_ship::x_coords() {
        return ship_x_coords;
    }
    
    /**
     * @return the y coords the ship is located at
    */
    bn::vector<int, MAX_SIZE> gam_ship::y_coords() {
        return ship_y_coords;
    }
    
    /**
     * @return true if the ship has been hit. False if not
    */
    bool gam_ship::is_hit() const {
        return ship_hit; 
    }

    bool gam_ship::try_to_hit(int column, int row) {
        if(ship_hit) {
            return false;
        }

        for (int i = 0; i < ship_size; i++) {

            int filled_column;
            int filled_row;

            if(ship_horizontal) {
                // Row stays the same and column changes
                filled_column = ship_x_coords[i]; 
                filled_row = ship_y_coords[0];
            }
            else {
                // Column stays the same while row changes (vertical)
                filled_column = ship_x_coords[0];
                filled_row = ship_y_coords[i]; 
            }

            if(column == filled_column && row == filled_row) { // If the ship is hit ..
                ship_hit = true;

                for (bn::sprite_ptr& sprite : ship_sprites) {
                    sprite.set_visible(false); // Hides the current square
                }

                return true; // Ship was hit so return true
            }
        }

        return false; // Missed so return false
    }
}