#pragma once

#include "mj/mj_game.h"
#include "cia/cia_player.h"
#include "cia/cia_shark.h"
#include <bn_regular_bg_ptr.h>
#include <bn_vector.h>
namespace cia
{
    static constexpr int sharkPoolSize = 16;

    class cia_oceandive : public mj::game
    {
    public:
        cia_oceandive(int completed_games, const mj::game_data &data);

        bn::fixed_rect rect() const;
        bn::string<16> title() const override;
        int total_frames() const override;
        mj::game_result play(const mj::game_data &data) override;
        bool victory() const override;
        void fade_in(const mj::game_data &data) override;
        void fade_out(const mj::game_data &data) override;

        void addNewShark(const mj::game_data &data);
        void set_up_game(mj::difficulty_level level);

    private:
        bn::regular_bg_ptr _bg;
        // Sprites
        player _player;

        // Vector to hold all sharks
        bn::vector<shark, sharkPoolSize> _sharkPool = {};

        // Frame per seconds and decrementing variable for it
        bn::fixed _frames = 60;
        bn::fixed _frameDecrement;


        // True once the shark hits the player
        bool _hit;

        // The sharks speed
        bn::fixed _sharksSpeed;

        // How much games have been completed
        int _completedGames;
    };

}