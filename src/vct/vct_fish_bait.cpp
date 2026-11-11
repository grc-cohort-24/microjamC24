#include "vct_fish_bait.h"

namespace vct 
{
<<<<<<< HEAD
    vct_fish_bait::vct_fish_bait(int completed_games, const mj::game_data& data) : mj::game("vct")
=======
    vct_fish_bait::vct_fish_bait([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data& data) : mj::game("vct"),
>>>>>>> 661d978887c5fe47806958f5af6836ecc6d8b02c
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