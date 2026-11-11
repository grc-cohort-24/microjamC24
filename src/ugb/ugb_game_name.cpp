#include <bn_string_view.h>
#include <bn_string.h>

#include "bn_sprite_items_fish1.h"
#include "bn_sprite_items_fish2.h"

#include "ugb/ugb_entity_manager.h"
#include "ugb/ugb_food.h"
#include "ugb/ugb_game_name.h"
#include "ugb/ugb_hook.h"
#include "ugb/ugb_state.h"

#include "mj/mj_game_list.h"
#include "mj/mj_game.h"

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
    ugb_game_name::ugb_game_name([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data& data) : 
    mj::game("ugb"), _player(constants::player::INITIAL_X, constants::player::INITIAL_Y, constants::player::SPEED) 
    {
        // Initialize score
        update_score(data.text_generator);
        // Spawn food
        for (int i = 0; i < 3; i++) {
            bn::fixed_point spawn_location = get_safe_spawn_loc(data.random);
            if (spawn_location.x() == constants::MAX_X) {
                continue; // Couldn't find a safe location
            }
            Food new_food(spawn_location);
            state::entities.push_back(new_food);
            state::food_count++;
        }
        // Spawn hooks
        for (int i = 0; i < 2; i++) {
            bn::fixed_point spawn_location = get_safe_spawn_loc(data.random);
            if (spawn_location.x() == constants::MAX_X) {
                continue; // Couldn't find a safe location
            }
            Hook new_hook(spawn_location);
            state::entities.push_back(new_hook);
        }
    }

    void ugb_game_name::update_score(const bn::sprite_text_generator& text_generator) {
        bn::string<constants::MAX_SCORE_CHARS> score_string = bn::to_string<constants::MAX_SCORE_CHARS>(state::score);
        text_generator.generate(constants::score::SCORE_X, constants::score::SCORE_Y, score_string, state::score_sprites);
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