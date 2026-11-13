#include "gam_selector.h"
#include <bn_keypad.h>
#include "bn_sprite_items_player.h"

namespace gam {
  /**
   * Constructor for a grid area selector
   * 
   * @param grid_column selector's column position on the grid
   * @param grid_row selector's row position on the grid
   */
  gam_selector::gam_selector(int start_column, int start_row) : 
  grid_column(start_column), 
  grid_row(start_row),
  selector_sprite(bn::sprite_items::player.create_sprite(
    -48 + start_column * 24,
    -48 + start_row * 24))
  
  {
    selector_sprite.set_scale(0.5);
  };

  /**
   * Checks player's input for movement and fire
   */
  void gam_selector::update(int columns, int rows) {
    if (bn::keypad::left_pressed() && grid_column > 0) {
      grid_column--;
    }
    if (bn::keypad::right_pressed() && grid_column < (columns -1)) {
      grid_column++;
    }
    if (bn::keypad::up_pressed() && grid_row > 0) {
      grid_row--;
    }
    if (bn::keypad::down_pressed() && grid_row < rows - 1) {
      grid_row++;
    }

    selector_sprite.set_position(-48 + grid_column * 24, -48 + grid_row * 24);

  }

  /**
   * @return selector's column position on the grid
   */
  int gam_selector::column() {
    return grid_column;
  }

  /**
   * @return selector's row position on the grid
   */
  int gam_selector::row() {
    return grid_row;
  }
}