#include "ugb/ugb_game_name.h"
#include "mj/mj_game_list.h"
#include "mj/mj_game.h"
#include "bn_string_view.h"
#include <bn_sprite_items_fish1.h>
#include <bn_sprite_items_fish2.h>
#include <bn_sprite_ptr.h>

// String arrays for the credits can go in an anonymous namespace
namespace
{
    constexpr bn::string_view code_credits[] = { "Nick B and Colin R" };
    constexpr bn::string_view graphics_credits[] = { "Nick B and Colin R" };
    constexpr bn::string_view sfx_credits[] = {" NA"};
    constexpr bn::string_view music_credits[] = {" NA"};
}

    // Macros used to add game to game list
    MJ_GAME_LIST_ADD(ugb::ugb_game_name)
    MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
    MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
    MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
    MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

namespace ugb {
    ugb::ugb_game_name::ugb_game_name([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data& data) : 
    mj::game("ugb"), _player(bn::fixed_point(0,0), 2) 
    {
        //PRE GAME SETUP
    }

    bn::string<16> ugb_game_name::title() const {
        return "UGB_Game";
    }

    int ugb_game_name::total_frames() const {
        return 600; // 10 seconds
    }

    bool ugb_game_name::victory() const {
        return false;
    }

    mj::game_result ugb_game_name::play([[maybe_unused]] const mj::game_data& data) {
        //GAME LOOP STUFF
        _player.update();
        
        //end
        mj::game_result result(victory(), false);
        return result;
    }

    void ugb_game_name::fade_in([[maybe_unused]] const mj::game_data &data) {

    }

    void ugb_game_name::fade_out([[maybe_unused]] const mj::game_data &data) {

    }

}