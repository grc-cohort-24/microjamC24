#include "gam_battleships.h"
#include "mj/mj_game_list.h"
#include "bn_regular_bg_items_gam_grid.h"
#include "bn_keypad.h"
#include "mj_difficulty_level.h"
#include "mj_game_data.h"
#include "mj_game.h"

namespace {
    constexpr bn::string_view code_credits[] = {"Garrett Fiorito", "Samuel Hyrych Zherzdyev"};
    constexpr bn::string_view graphics_credits[] = {"Garrett Fiorito", "Samuel Hyrych Zherzdyev"};
}

MJ_GAME_LIST_ADD(gam::gam_battleships)

MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)

namespace gam {

    /**
   * Constructor for an instance of an gam_battleships
   * 
   * First item in the initializer list MUST be a call to the superclass, mj::game with the identifier for the microgame.
   * 
   * @param completed_games how many microgames the player has completed so far
   * @param data shared information, such as a rng and number of frames left in the microgame
   */
  gam_battleships::gam_battleships(
    int completed_games, 
    const mj::game_data& data) : 
    mj::game("gam"),
    _game_grid(5, 5),
    _game_selector(0, 0),
    _game_background(bn::regular_bg_items::gam_grid.create_bg(0, 0))
  {
    mj::difficulty_level difficulty = recommended_difficulty_level(completed_games, data);

        if(difficulty == mj::difficulty_level::EASY) {
            _game_grid.new_ship(3, data.random);
        }
        else if(difficulty == mj::difficulty_level::NORMAL) {
            _game_grid.new_ship(3, data.random);
            _game_grid.new_ship(4, data.random);
        }
        else if(difficulty == mj::difficulty_level::HARD) {
            _game_grid.new_ship(4, data.random);
            _game_grid.new_ship(3, data.random);
            _game_grid.new_ship(2, data.random);
        }
  }

  /**
   * The instructions given to the player at the beginning of the microgame.
   * 
   * Must be <= 16 characters long
   */
  bn::string<16> gam_battleships::title() const {
      return "Destroy ships";
  }

  /**
   * How long the timer for the game should be set to in frames.
   * 
   * GBA runs at approx 60 frames per second.
   */
  int gam_battleships::total_frames() const {
      return 600; // 300 frames at 60fps = 5 seconds
  }

  /**
   * play is repeatedly called while the microgame is playing.
   * 
   * You can think of it as what previously was in the while event loop.
   * You do NOT need to write your own while event loop
   * You do NOT need to call bn::core::update()
   * 
   * @param data shared information, such as a rng and number of frames left in the microgame
   * @return the mj::game result indicating whether the game has finished and whether the title should be hidden
   */
  mj::game_result gam_battleships::play([[maybe_unused]] const mj::game_data& data)
  {

      _game_grid.update_animations();

      _game_selector.update(_game_grid.columns(), _game_grid.rows());

      if(bn::keypad::a_pressed()) {
        _game_grid.fire(_game_selector.column(), _game_selector.row());
      }

      // Show only the currently selected cell and all cells of sunk ships
      _game_grid.update_visibility(_game_selector.column(), _game_selector.row());

      bool is_finished = victory() && !_game_grid.animation_is_running(); 

      mj::game_result result(is_finished, false);
      return result;
  }

  /**
   * Returns whether the player has won the microgame.
   * 
   * In this particular microgame the player wins if all ships are destroyed.
   */
  bool gam_battleships::victory() const {
      return _game_grid.ships_left() == 0;
  }

  /**
   * Called repeatedly as the game fades into view. Unused for this particular microgame.
   * 
   * @param data shared information, such as a rng and number of frames left in the microgame
   */
  void gam_battleships::fade_in([[maybe_unused]] const mj::game_data& data)
  {
  }

  /**
   * Called repeatedly as the game fades into view. Unused for this particular microgame.
   * 
   * @param data shared information, such as a rng and number of frames left in the microgame
   */
  void gam_battleships::fade_out([[maybe_unused]] const mj::game_data& data)
  {
  }


}