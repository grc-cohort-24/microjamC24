#include "bar_snap_em_up.h"
#include "mj/mj_game_list.h"

#include "bn_regular_bg_items_bar_ocean.h"

#define FLOOR (80 - 16)
#define CEILING (-72 - 8)

namespace
{
   constexpr bn::string_view code_credits[] = {"TheArticWinter, crex424"};
   constexpr bn::string_view graphics_credits[] = {""};
   constexpr bn::string_view sfx_credits[] = {""};
   constexpr bn::string_view music_credits[] = {""};
}

// Macros used to add game to game list
MJ_GAME_LIST_ADD(bar::bar_snap_em_up) // The class of the game is used here
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

namespace bar
{
   static constexpr bn::fixed position_left = -32;
   static constexpr bn::fixed position_right = 32;

   static constexpr bn::fixed player_position_y = 20;
   static constexpr bn::size player_size = {16, 16};

   static constexpr bn::fixed coin_position_y = CEILING;
   static constexpr bn::size coin_size = {8, 8};

   bar_snap_em_up::bar_snap_em_up([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data &data) : mj::game("bar"),
                                                                                                                      _player_arms(),
                                                                                                                      _coins(),
                                                                                                                      _background(bn::regular_bg_items::bar_ocean.create_bg()),
                                                                                                                      _kraken(bn::sprite_items::bar_kraken.create_sprite(0, FLOOR - 15)),
                                                                                                                      rng(data.random),
                                                                                                                      kraken_animation(bn::create_sprite_animate_action_forever(_kraken, 10, bn::sprite_items::bar_kraken.tiles_item(), 0, 1, 2, 1, 0))
   {
      game_timer = 0;
      coin_hit_count = 0;
      kraken_lives = 3;
      coin_target_reached = false;
      completed_games_global = completed_games;

      _player_arms.push_back(bar_player(position_left, player_position_y, player_size));
      _player_arms.push_back(bar_player(position_right, player_position_y, player_size));

      bar_spawn_coin(_coins, position_left, coin_position_y, _recommended_coin_speed(recommended_difficulty_level(completed_games, data)), coin_size);
   }

   bn::string<16> bar_snap_em_up::title() const
   {
      return "Snap Em Up!";
   }

   int bar_snap_em_up::total_frames() const
   {
      return 300;
   }

   bn::fixed bar_snap_em_up::_recommended_coin_speed(mj::difficulty_level difficulty)
   {
      if (difficulty == mj::difficulty_level::EASY)
      {
         return 2;
      }
      else if (difficulty == mj::difficulty_level::NORMAL)
      {
         return 2.5;
      }
      else if (difficulty == mj::difficulty_level::HARD)
      {
         return 3.2;
      }
      return 1;
   }

   bn::fixed bar_snap_em_up::_recommended_spawn_speed(mj::difficulty_level difficulty)
   {
      if (difficulty == mj::difficulty_level::EASY)
      {
         return 35;
      }
      else if (difficulty == mj::difficulty_level::NORMAL)
      {
         return 28;
      }
      return 19;
   }

   int bar_snap_em_up::_recommended_target_count(mj::difficulty_level difficulty)
   {
      if (difficulty == mj::difficulty_level::EASY)
      {
         return 5;
      }
      else if (difficulty == mj::difficulty_level::NORMAL)
      {
         return 7;
      }
      return 10;
   }

   mj::game_result bar_snap_em_up::play([[maybe_unused]] const mj::game_data &data)
   {
      kraken_animation.update();
      for (bar_coin &coin : _coins)
      {
         coin.update();
         _player_arms[0].update_lower_left(coin);
         _player_arms[1].update_lower_right(coin);
      }

      for (int i = _coins.size() - 1; i >= 0; i--)
      {
         if (_coins[i].is_collided())
         {
            _coins.erase(_coins.begin() + i);
            coin_hit_count++;
         }
         if (_coins[i].get_sprite().y() >= FLOOR)
         {
            _coins.erase(_coins.begin() + i);
            // kraken_lives--;
         }
      }

      if (game_timer >= _recommended_spawn_speed(recommended_difficulty_level(completed_games_global, data)))
      {
         // Spawn Rate Logic
         bn::fixed random_pos;
         game_timer = 0;

         if (rng.get_bool())
            random_pos = position_left;
         else
            random_pos = position_right;

         bar_spawn_coin(_coins, random_pos, coin_position_y, _recommended_coin_speed(recommended_difficulty_level(completed_games_global, data)), coin_size);
         rng = data.random;
      }

      if (coin_hit_count == _recommended_target_count(recommended_difficulty_level(completed_games_global, data)))
         coin_target_reached = true;

      game_timer++;
      mj::game_result result(victory(), false);
      return result;
   }

   bool bar_snap_em_up::victory() const
   {
      return coin_target_reached;
   }

   void bar_snap_em_up::fade_in([[maybe_unused]] const mj::game_data &data)
   {
   }

   void bar_snap_em_up::fade_out([[maybe_unused]] const mj::game_data &data)
   {
      _coins.clear();
   }
}