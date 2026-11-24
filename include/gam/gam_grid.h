#pragma once
#include <bn_vector.h>
#include <bn_random.h>
#include "gam_ship.h"

namespace gam {

  const int MAX_SHIPS = 3;

  class gam_grid {
    public:
      /**
       * Grid for battleships game
       * 
       * @param columns number of grid columns
       * @param rows number of grid rows
       */
      gam_grid(int columns, int rows);

      /**
       * Creates a new ship with random placement and orientation
       * 
       * @param size number of grid areas ship occupies
       */
      void new_ship(int size, bn::random& rng);

      // Tell every ship which cell the player is selecting. So each ship knows which cells to show
      void update_visibility(int selected_column, int selected_row);


      /**
       * @return number of ships that are not sunk
       */
      int ships_left() const;
      /**
       * @return number of grid columns
       */
      int columns();

      /**
       * @return number of grid rows
       */
      int rows();

      void fire(int column, int row);

      // Move the animation forward
      void update_animations();

      // Store if any ship is actively in the animation process
      bool animation_is_running() const;

    private:
      int _grid_columns;
      int _grid_rows;
      bn::vector<gam::gam_ship, MAX_SHIPS> _ships;
      static constexpr int _placement_attempt = 1000;

      /**
       * @param first_column starting column for new ship
       * @param first_row starting row for new ship
       * @param size size of new ship
       * @param horizontal orientation of new ship
       * @return whether any ship occupies specified grid areas
       */
      bool occupied(int first_column, int first_row, int size, bool horizonal);
  };
}