#include "vct_fish_bait.h"

#include "mj/mj_game_list.h"

//Game credits
namespace
{
    constexpr bn::string_view code_credits[] = { "Moratsu", "Raul" };
    constexpr bn::string_view graphics_credits[] = { "Moratsu", "Raul" };
    constexpr bn::string_view sfx_credits[] = {""};
    constexpr bn::string_view music_credits[] = {""};
}

MJ_GAME_LIST_ADD(vct::vct_fish_bait)
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

//Declarations
namespace vct 
{
    //Constructor for an instance of an vct_fish_bait
    vct_fish_bait::vct_fish_bait([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data& data) : mj::game("vct"),
    _bg(bn::regular_bg_items::vct_background.create_bg(0, 0)),
    _player({20, 20}, 2),
    _caught_fish(bn::sprite_items::vct_angler.create_sprite(0, 60))
      
    {
    }

    //Game title/ the instructions to give to the player
    bn::string<16> vct_fish_bait::title() const 
    {
        return "Fish Bait";
    }

    //How long the game lasts for
    int vct_fish_bait::total_frames() const 
    {
        return 600;
    }

    //Basically the "while" loop of our code, constantly updates player
    //as play constantly updates.
    mj::game_result vct_fish_bait::play(const mj::game_data& data) 
    {
        //allows us to be able to adjust how fast the fish falls down the screen/sinks back
        //in wave 6 this can work as a diffuculty adjuster
        _sink_timer++;
        if (_sink_timer > 4) { 
            _caught_fish.set_y(_caught_fish.y() + 1);
            _sink_timer = 0; 
        }

       mj::game_result result(victory(), false);
       _player.update(data.random, data.text_generator);
       return result;
    }
    
    //Checks if the player wins
    bool vct_fish_bait::victory() const 
    {
        return _player.qte_complete();
    }
    
    //Most likely unused for our game
    void vct_fish_bait::fade_in([[maybe_unused]] const mj::game_data& data) 
    {
    }
    
    //Most likely unused for our game
    void vct_fish_bait::fade_out([[maybe_unused]] const mj::game_data& data) 
    {
    }
}