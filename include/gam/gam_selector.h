#pragma once
#include "bn_sprite_ptr.h"

namespace gam {
  class gam_selector {
    public:
      /**
       * Constructor for a grid area selector
       * 
       * @param grid_column selector's column position on the grid
       * @param grid_row selector's row position on the grid
       */
      gam_selector(int start_column, int start_row);

      /**
       * Checks player's input for movement and fire
       */
      void update(int columns, int rows);

      /**
       * @return selector's column position on the grid
       */
      int column();
      
      /**
       * @return selector's row position on the grid
       */
      int row();

    private:
      int grid_column;
      int grid_row;
      bn::sprite_ptr selector_sprite;
  };
}