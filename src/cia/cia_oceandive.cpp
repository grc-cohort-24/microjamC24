#include "cia_oceandive.h"
#include "mj/mj_game_list.h"
#include "cia/cia_shark.h"
#include <bn_regular_bg_ptr.h>
#include <bn_regular_bg_items_cia_ocean_bg.h>
namespace
{
    constexpr bn::string_view code_credits[] = {"Ali", "Alex"};
    constexpr bn::string_view graphics_credits[] = {""};
    constexpr bn::string_view sfx_credits[] = {""};
    constexpr bn::string_view music_credits[] = {""};
}

MJ_GAME_LIST_ADD(cia::cia_oceandive)
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

namespace cia
{
    void cia_oceandive::set_up_game(mj::difficulty_level level) {
        // create a if statement for an easy mode
        if (level == mj::difficulty_level::EASY)
        {
            _frameDecrement = 1.22;
            _sharksSpeed = 0.41;
        }
        // make a medium mode
        else if (level == mj::difficulty_level::NORMAL)
        {
            _frameDecrement = 1.32;
            _sharksSpeed = 0.45;
        }
        // Assuming that we didn't go into the other if statements (This is for hard mode)
        else
        {
            _frameDecrement = 1.55;
            _sharksSpeed = 0.5;
        }
    }

    void cia_oceandive::addNewShark(const mj::game_data &data) {
        if (!_sharkPool.full()) {
            _sharkPool.push_back(shark(data.random, _sharksSpeed));
        }
    }


    cia_oceandive::cia_oceandive([[maybe_unused]] int completed_game, [[maybe_unused]] const mj::game_data &data) : mj::game("cia"),
                                                                                                _bg(bn::regular_bg_items::cia_ocean_bg.create_bg(0, 0)),
                                                                                                _player(player({0, 20}, 1)),
                                                                                                _hit(false)
    {
        set_up_game(recommended_difficulty_level(completed_game, data));
        _completedGames = completed_game;
    }

    bn::string<16> cia_oceandive::title() const
    {
        return "Avoid The Shark!";
    }

    int cia_oceandive::total_frames() const
    {
        return 300;
    }

    mj::game_result cia_oceandive::play(const mj::game_data &data)
    {
        _player.update();

        for (shark& s : _sharkPool) {
            s.update(_player);

            // If the player intersects with the shark, the player loses.
            if (_player.rect().intersects(s.rect()))
            {
                _hit = true;
            }
        }

        _frames -= _frameDecrement;

        if (_frames < 0) {
            addNewShark(data);
            _frames = 60;
        }   

        return mj::game_result(_hit, false);
    }

    bool cia_oceandive::victory() const
    {
        return !_hit;
    }

    void cia_oceandive::fade_in(const mj::game_data &)
    {
    }

    void cia_oceandive::fade_out(const mj::game_data &)
    {
    }
}