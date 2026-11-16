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
<<<<<<< HEAD
    _player({20, 20}, _recommended_buttons(
        recommended_difficulty_level(completed_games, data))) 
        //I'm still not entirely sure what the amount of
        //completed games is to move onto the next level is.
        //I've experimented with different multiplier numbers for about 30 minutes and 8
        //is what seems to work for my game, so I'll stick with it. (I know this isn't how
        //it's supposed to be done, but this was really confusing)
=======
    _player({20, 20}, 3 + completed_games)
      
>>>>>>> parent of eb862fe (FINALLY finished the difficulty levels for the QTE buttons)
    {
    }

    //Game title/ the instructions to give to the player
    bn::string<16> vct_fish_bait::title() const 
    {
        return "Fish Bait";
    }

    int vct_fish_bait::_recommended_buttons(mj::difficulty_level difficulty)
    {
        if(difficulty == mj::difficulty_level::HARD)
        {
            return 7;
        }
        else if(difficulty == mj::difficulty_level::NORMAL)
        {
            return 10;
        }
        else
        {
            return 15;
        }
    }
    
    //How long the game lasts for
    int vct_fish_bait::total_frames() const 
    {
        return 600; //10 seconds 60 fps
    }

    //Basically the "while" loop of our code, constantly updates player
    //as play constantly updates.
    mj::game_result vct_fish_bait::play(const mj::game_data& data) 
    {
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