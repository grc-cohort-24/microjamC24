#include "bnc_squid_escape.h"

#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_sprite_ptr.h"
#include <bn_log.h>
#include "mj/mj_game_list.h"
#include "bnc/bnc_squid.h"
#include "bnc/bnc_whale.h"


// String arrays for the credits can go in an anonymous namespace
namespace
{
    constexpr bn::string_view code_credits[] = { "Brook Carter, Cristian Rosas B." };
    constexpr bn::string_view graphics_credits[] = { "Kenney Game Assets" };
    constexpr bn::string_view sfx_credits[] = {""};
    constexpr bn::string_view music_credits[] = {""};
}

// Macros used to add game to game list
MJ_GAME_LIST_ADD(bnc::bnc_fish_escape) // The class of the game is used here
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)


namespace bnc
{

    /**
 * Constructor for an instance of an bnc_fish_escape
 * 
 * First item in the initializer list MUST be a call to the superclass, mj::game with the identifier for the microgame.
 * 
 * @param completed_games how many microgames the player has completed so far
 * @param data shared information, such as a rng and number of frames left in the microgame
 */
    bnc_fish_escape::bnc_fish_escape(
        [[maybe_unused]] int completed_games,
        [[maybe_unused]] const mj::game_data& data) : mj::game("bnc"), 
        _squid(bn::fixed_point(X_START, Y_START), SPEED)
    {

        while(_whale_vector.size() < _whale_increase(recommended_difficulty_level(completed_games * 9, data))) {

            _whale_vector.push_back(Whale(
            data.random.get_unbiased_fixed(MIN_X, MAX_X),
            data.random.get_unbiased_fixed(MIN_Y, MAX_Y),
            WHALE_SPEED));

        }
    };

    /**
 * The instructions given to the player at the beginning of the microgame.
 * 
 * Must be <= 16 characters long
 */
    bn::string<16> bnc_fish_escape::title() const {
    return "Avoid Whales!";
}

int bnc_fish_escape::_whale_increase(mj::difficulty_level difficulty) {
    if(difficulty == mj::difficulty_level::EASY) {
        return 3;
    } else if (difficulty == mj::difficulty_level::NORMAL) {
        return 4;
    } 
    return 5;
}

/*
 * How long the timer for the game should be set to in frames.
 * 
 * GBA runs at approx 60 frames per second.
 */
int bnc_fish_escape::total_frames() const {
    return 600; // 300 frames at 60fps = 5 seconds
}

/**
 * play is repeatedly called while the microgame is playing.
 * 
 * You can think of it as what previously was in the while event loop.
 * You do NOT need to write your own while event loop
 * You do NOT need to call bn::core::update()
 * 
 * @param data shared information, such as a rng and number of frames left in the microgame
 * @return the mj::game result indicating whether the game has finished and whether the title should be hidden
 */
mj::game_result bnc_fish_escape::play([[maybe_unused]] const mj::game_data& data)
{
    // update the player position
    _squid.update();

    //add another boolean for individual sharks
    bool _caught_squid = false;
    
    //add the for loop to loop over enemies
    for(int i = 0; i< _whale_vector.size(); i++){
        //update the vector to the players location using the index
        _whale_vector[i].update(_squid);

        // Reset the current score and player position if the player collides with enemy
        if(_whale_vector[i]._whale_collision() == true) {

            _caught_squid = true;
        }
    }

    // Creates a game result indicating whether the game is finished and whether the title should be hidden early
    // For this game the game should end early if the player has won (if victory returns true)
    // The title is not hidden early (false is passed), so the title disappears at the default time
    mj::game_result result(victory() || _caught_squid, false);
    return result;
}

/**
 * Returns whether the player has won the microgame.
 * 
 * In this particular microgame the player wins if they make the ball leave the screen.
 */
bool bnc_fish_escape::victory() const {
    return _squid.out_of_bounds();
}

/**
 * Called repeatedly as the game fades into view. Unused for this particular microgame.
 * 
 * @param data shared information, such as a rng and number of frames left in the microgame
 */
void bnc_fish_escape::fade_in([[maybe_unused]] const mj::game_data& data)
{
}

/**
 * Called repeatedly as the game fades into view. Unused for this particular microgame.
 * 
 * @param data shared information, such as a rng and number of frames left in the microgame
 */
void bnc_fish_escape::fade_out([[maybe_unused]] const mj::game_data& data)
{
}



}
