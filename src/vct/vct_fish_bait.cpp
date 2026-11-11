#include "vct_fish_bait.h"

#include "mj/mj_game_list.h"

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

namespace vct 
{
    vct_fish_bait::vct_fish_bait([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data& data) : mj::game("vct")
    {
    }

    bn::string<16> vct_fish_bait::title() const 
    {
        return "Fish Bait";
    }

    int vct_fish_bait::total_frames() const 
    {
        return 300;
    }

    mj::game_result vct_fish_bait::play([[maybe_unused]] const mj::game_data& data) 
    {
       mj::game_result result(victory(), false);
       return result;
    }
    
    bool vct_fish_bait::victory() const 
    {
        return false;
    }
    
    void vct_fish_bait::fade_in([[maybe_unused]] const mj::game_data& data) 
    {
    }
    
    void vct_fish_bait::fade_out([[maybe_unused]] const mj::game_data& data) 
    {
    }
}