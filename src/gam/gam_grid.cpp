#include "gam_grid.h"

namespace gam {
       /**
       * Grid for battleships game
       * 
       * @param columns number of grid columns
       * @param rows number of grid rows
       */
      gam_grid::gam_grid(int columns, int rows) :
      grid_columns(columns), grid_rows(rows) {

      }

      /**
       * Creates a new ship with random placement and orientation
       * 
       * @param size number of grid areas ship occupies
       */
      void gam_grid::new_ship(int size) {
        if (ships.size() < MAX_SHIPS) {
          ships.push_back(
            gam::gam_ship(size,
            random.get_bool(),
            random.get_int(columns()),
            random.get_int(rows()))
          );
        }
      }

      /**
       * @return number of ships that are not sunk
       */
      int gam_grid::ships_left() const {
        int ships_remaining = 0;

        for (const gam_ship& ship : ships) {
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
        return grid_columns;
      }

      /**
       * @return number of grid rows
       */
      int gam_grid::rows() {
        return grid_rows;
      }


      void gam_grid::fire(int column, int row) {
        for (gam_ship& ship : ships) {
          ship.try_to_hit(column, row);
        }
      }
    }