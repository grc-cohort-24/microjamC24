#pragma once

#include <bn_vector.h>
#include <bn_regular_bg_ptr.h>
#include <bn_sprite_animate_actions.h>


#include "mj/mj_game.h"
#include "bar/bar_player.h"
#include "bar/bar_coin.h"
#include "bar/bar_create_bounding_box.h"
#include "bar/bar_spawn_coin.h"
#include "bn_sprite_items_bar_kraken.h"
#include "bar_constants.h"


// All game functionality, classes, fields
namespace bar
{
    class bar_snap_em_up : public mj::game
    {
    public:
        bar_snap_em_up(int complete_games, const mj::game_data &data);

        bn::string<16> title() const override;

        int total_frames() const override;

        mj::game_result play(const mj::game_data &data) override;

        bool victory() const override;

        void fade_in(const mj::game_data &data) override;

        void fade_out(const mj::game_data &data) override;

    private:
        bn::vector<bar_player, 2> _player_arms;
        bn::vector<bar_coin, MAX_COINS> _coins;
        bn::regular_bg_ptr _background;
        bn::sprite_ptr _kraken;
        bn::random &rng;
        bn::sprite_animate_action<5> kraken_animation;
        bn::fixed _recommended_coin_speed(mj::difficulty_level difficulty);
        bn::fixed _recommended_spawn_speed(mj::difficulty_level difficulty);
        int _recommended_target_count(mj::difficulty_level difficulty);
        int coin_hit_count;
        int completed_games_global;
        int game_timer;
        int kraken_lives;
        bool coin_target_reached;
    };
}