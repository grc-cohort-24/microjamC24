#include "vct_fish_bait.h"

namespace vct 
{
    vct_fish_bait::vct_fish_bait(int completed_games, const mj::game_data& data) : mj::game("vct")
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

    mj::game_result vct_fish_bait::play(const mj::game_data& data) 
    {
       mj::game_result result(victory(), false);
       return result;
    }
    
    bool vct_fish_bait::victory() const 
    {
        return false;
    }
    
    void vct_fish_bait::fade_in(const mj::game_data& data) 
    {
    }
    
    void vct_fish_bait::fade_out(const mj::game_data& data) 
    {
    }
}