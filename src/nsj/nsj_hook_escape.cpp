#include "nsj_hook_escape.h"
#include "mj/mj_game_list.h"
#include "nsj_Enemy.h"
#include "nsj_boundingBox.h"
#include "bn_regular_bg_items_nsj_background.h"

namespace
{
   constexpr bn::string_view code_credits[] = {"Necobi Williams", "Samantha Jimenez"};
   constexpr bn::string_view graphics_credits[] = {""};
   constexpr bn::string_view sfx_credits[] = {""};
   constexpr bn::string_view music_credits[] = {""};
}

MJ_GAME_LIST_ADD(nsj::nsj_hook_escape)
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

namespace nsj
{
   nsj_hook_escape::nsj_hook_escape([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data &data) : mj::game("nsj"),
                                                                                                                        _player({0, 0}, 2),
                                                                                                                        _background(bn::regular_bg_items::nsj_background.create_bg(0, 0))

   {
      mj::difficulty_level difficulty =
          recommended_difficulty_level(completed_games, data);

      bn::fixed speed = _recommended_hook_speed(recommended_difficulty_level(completed_games, data));

      _enemies.push_back(Enemy(30, -30, speed, -speed, data.random));
      _enemies.push_back(Enemy(-100, 40, speed + 0.5, speed, data.random));
      _enemies.push_back(Enemy(100, -40, speed, -speed, data.random));
      if (difficulty == mj::difficulty_level::NORMAL ||
          difficulty == mj::difficulty_level::HARD)
      {
         _sharks.push_back(
             Shark(-80, -40, _recommended_shark_speed(difficulty)));
      }
   }

   bn::string<16> nsj_hook_escape::title() const
   {
      return "Don't Get Caught";
   }

   bn::fixed nsj_hook_escape::_recommended_hook_speed(mj::difficulty_level difficulty)
   {
      if (difficulty == mj::difficulty_level::EASY)
      {
         return .50;
      }
      else if (difficulty == mj::difficulty_level::NORMAL)
      {
         return .75;
      }
      return 1;
   }

   bn::fixed nsj_hook_escape::_recommended_shark_speed(mj::difficulty_level difficulty)
   {
      if (difficulty == mj::difficulty_level::EASY)
      {
         return .50;
      }
      else if (difficulty == mj::difficulty_level::NORMAL)
      {
         return .75;
      }
      return 1;
   }

   int nsj_hook_escape::total_frames() const
   {
      return 600;
   }

   mj::game_result nsj_hook_escape::play([[maybe_unused]] const mj::game_data &data)
   {

      _player.update();
      for (int i = 0; i < _enemies.size(); i++)
      {
         _enemies[i].update();

         if (_enemies[i].get_bounding_box().intersects(_player.get_bounding_box()))
         {
            _hooked = true;
         }
      }

      for (Shark &shark : _sharks)
      {
         shark.update(_player);

         if (shark.get_bounding_box().intersects(_player.get_bounding_box()))
         {
            _hooked = true;
         }
      }

      // Creates a game result indicating whether the game is finished and whether the title should be hidden early
      // For this game the game should end early if the player has won (if victory returns true)
      // The title is not hidden early (false is passed), so the title disappears at the default time
      mj::game_result result(_hooked, false);
      return result;
   }

   bool nsj_hook_escape::victory() const

   {
      return !_hooked;
   }

   void nsj_hook_escape::fade_in([[maybe_unused]] const mj::game_data &data)
   {
   }

   void nsj_hook_escape::fade_out([[maybe_unused]] const mj::game_data &data)
   {
   }
}
