#pragma once

#include <bn_regular_bg_ptr.h>
#include <bn_sprite_ptr.h>
#include <bn_random.h>

#include "mj/mj_game.h"
#include "mck_player.h"
#include "mck_enemy.h"
#include "mck_urchin.h"

namespace mck {

    class mck_shark_dodge : public mj::game {

        public:
        mck_shark_dodge(int completed_games, const mj::game_data& data);

        bn::string<16> title() const override;
        int total_frames() const override;
        mj::game_result play(const mj::game_data& data) override;
        bool victory() const override;
        void fade_in(const mj::game_data& data) override;
        void fade_out(const mj::game_data& data) override;

        private:
        // The character that the player can move
        player _player;
        static constexpr int TOTAL_FRAMES = 600;
        static constexpr int WAVE_INTERVAL_FRAMES = 50;
        static constexpr int MAX_ENEMIES = 52;
        bn::vector<enemy, MAX_ENEMIES> _enemies;
        urchin _urchin;
        bn::random rand_spawn;
        bool _hit = false;
        int _timer = 0;
        const bn::fixed _enemy_speeds[3] = {0.7, 0.9, 1};
        const bn::fixed _wave_sizes[3] = {2, 3, 4};
        bn::fixed _enemy_speed;
        bn::fixed _wave_size;
        bn::regular_bg_ptr _background;

        // Determines Enemy speed
        bn::fixed enemy_speed(mj::difficulty_level difficulty);

        // Determines wave size
        bn::fixed wave_size(mj::difficulty_level difficulty);

        /**
         * selects a location for the urchin
         */
        bn::fixed_point urchin_location();
    };

}