#include "gam_grid.h"

namespace gam {
       /**
       * Grid for battleships game
       * 
       * @param columns number of grid columns
       * @param rows number of grid rows
       */
      gam_grid::gam_grid(int columns, int rows) :
      _grid_columns(columns), _grid_rows(rows) {

      }

      /**
       * Creates a new ship with random placement and orientation
       * 
       * @param size number of grid areas ship occupies
       */
      void gam_grid::new_ship(int size, bn::random& rng)
      {
          // Catch unsupported ship sizes or a full board of ships
          if (_ships.size() >= MAX_SHIPS || size < 1 ||
              size > MAX_SIZE ||
              size > _grid_columns ||
              size > _grid_rows)
          {
              return;
          }

          for (int attempt = 0; attempt < _placement_attempt; attempt++)
          {
              bool horizontal = rng.get_bool();
              int column;
              int row;

              if (horizontal)
              {
                  column = rng.get_int(_grid_columns - size + 1);
                  row = rng.get_int(_grid_rows);
              }
              else
              {
                  column = rng.get_int(_grid_columns);
                  row = rng.get_int(_grid_rows - size + 1);
              }
              if (occupied(column, row, size, horizontal))
              {
                  _ships.push_back(gam_ship(size, horizontal, column, row));
                  return;
              }
          }
      }

      /**
       * @return number of ships that are not sunk
       */
      int gam_grid::ships_left() const {
        int ships_remaining = 0;

        for (const gam_ship& ship : _ships) {
          if(!ship.is_hit()) {
            ships_remaining++;
          }
        }
        return ships_remaining;
      }

      /**
       * @return number of grid columns
       */
      int gam_grid::columns() {
        return _grid_columns;
      }

      /**
       * @return number of grid rows
       */
      int gam_grid::rows() {
        return _grid_rows;
      }


      void gam_grid::fire(int column, int row) {
        for (gam_ship& ship : _ships) {
          ship.try_to_hit(column, row);
        }
      }

      /**
       * @param first_column starting column for new ship
       * @param first_row starting row for new ship
       * @param size size of new ship
       * @param horizontal orientation of new ship
       * @return whether any ship occupies specified grid areas
       */
      bool gam_grid::occupied(int first_column, int first_row, int size, bool horizonal) {
        for (gam_ship& other_ship : _ships) {
          if (horizonal) {
            for (int i = first_column; i < first_column + size; i++) {
              for (int x : other_ship.x_coords()) {
                for (int y : other_ship.y_coords()) {
                  if (i == x && first_row == y) {
                    return false;
                  }
                }
              }
            }
          } else {
            for (int j = first_row; j < first_row + size; j++) {
              for (int x : other_ship.x_coords()) {
                for (int y : other_ship.y_coords()) {
                  if (j == y && first_column == x) {
                    return false;
                  }
                }
              }
            }
          }
        }

        return true;
      }

      void gam_grid::update_visibility(int selected_column, int selected_row) {
        // Update the stored ships (The grid owns the ships)
        for (gam_ship& ship: _ships) {
          ship.update_visibility(selected_column, selected_row);
        }
      }

      void gam_grid::update_animations() {
        for (gam_ship& ship : _ships) {
          // Update the ships stored on the grid
          ship.update_animation();
        }
      }

      bool gam_grid::animation_is_running() const {
        for (const gam_ship& ship : _ships) {
          // If even one ship is still in the animation process return true
          if (ship.animation_is_running()) {
            return true;
          }
        }
        return false;
      }
    }