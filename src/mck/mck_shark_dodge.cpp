#include "mck/mck_shark_dodge.h"

#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"  
#include <bn_random.h>

#include "bn_regular_bg_items_mck_ocean_background.h"

#include "mj/mj_game_list.h"
#include "mck/mck_bounds.h"

namespace
{
    // TODO add names to credits as appropriate
    constexpr bn::string_view code_credits[] = { "Matthew Renner", "Connor Stimpson", "Kevin Flores-Gonzalez" };
    constexpr bn::string_view graphics_credits[] = { "Matthew Renner", "Connor Stimpson", "Kevin Flores-Gonzalez" };
    //constexpr bn::string_view sfx_credits[] = {};
    //constexpr bn::string_view music_credits[] = {};
}

MJ_GAME_LIST_ADD(mck::mck_shark_dodge)
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
//MJ_GAME_LIST_ADD_MUSIC_CREDITS(sfx_credits)
//MJ_GAME_LIST_ADD_SFX_CREDITS(music_credits)

namespace mck {
    mck_shark_dodge::mck_shark_dodge([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data& data):
        mj::game("mck"),
        _player(player({0, 0}, 1)),
        _urchin(urchin(urchin_location())),
        _enemy_speed(enemy_speed(recommended_difficulty_level(completed_games, data))),
        _wave_size(wave_size(recommended_difficulty_level(completed_games, data))),
        _background(bn::regular_bg_items::mck_ocean_background.create_bg())
    {
        _enemies.clear(); // clear the enemies array to make sure it is not overfilled during gameplay
        for (int i = 0; i < _wave_size; i++) { // add enemies to the vector based on difficulty
            _enemies.push_back(enemy(_enemy_speed, data.random));
        }
    }

    bn::string<16> mck_shark_dodge::title() const {
        return "Dodge!";
    }

    int mck_shark_dodge::total_frames() const {
    return TOTAL_FRAMES; // 600 frames at 60fps = 10 seconds
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
mj::game_result mck_shark_dodge::play([[maybe_unused]] const mj::game_data& data)
{
    // update the player position
    _player.update();

    // update all enemy positions, check for collisions
    for (enemy& e : _enemies) {
        e.update();
        if(_player.hitbox().intersects(e.hitbox()) ){
            _hit = true;
            break; // game has ended: no need to iterate further
        }
    }

    if(_player.hitbox().intersects(_urchin.hitbox())) {
        _hit = true;
    }

    if (!_hit) { // proceed only if player has not lost
        _timer++;
        if (_timer % WAVE_INTERVAL_FRAMES == 0) { // every 50 frames, make _wave_size more sharks
            for (int i = 0; i < _wave_size; i++) {
                _enemies.push_back(enemy(_enemy_speed, data.random));
            }
        }
    }

    _urchin.update();

    mj::game_result result(_hit, false);
    return result;
}

/**
 * Returns whether the player has won the microgame.
 * 
 * In this particular microgame the player wins if they make the ball leave the screen.
 */
bool mck_shark_dodge::victory() const {
    return !_hit;
}

/**
 * Called repeatedly as the game fades into view. Unused for this particular microgame.
 * 
 * @param data shared information, such as a rng and number of frames left in the microgame
 */
void mck_shark_dodge::fade_in([[maybe_unused]] const mj::game_data& data)
{
}

/**
 * Called repeatedly as the game fades into view. Unused for this particular microgame.
 * 
 * @param data shared information, such as a rng and number of frames left in the microgame
 */
void mck_shark_dodge::fade_out([[maybe_unused]] const mj::game_data& data)
{
}

// Determines Enemy speed
bn::fixed mck_shark_dodge::enemy_speed(mj::difficulty_level difficulty){
    if(difficulty == mj::difficulty_level::EASY) {
        return _enemy_speeds[0];
    } else if (difficulty == mj::difficulty_level::NORMAL) {
        return _enemy_speeds[1];
    } 
    return _enemy_speeds[2];
};

// Determines wave size
bn::fixed mck_shark_dodge::wave_size(mj::difficulty_level difficulty){
    if(difficulty == mj::difficulty_level::EASY) {
        return _wave_sizes[0];
    } else if (difficulty == mj::difficulty_level::NORMAL) {
        return _wave_sizes[1];
    } 
    return _wave_sizes[2];
};

/**
 * selects a location for the urchin
 */
bn::fixed_point mck_shark_dodge::urchin_location() {

    
    int spawn_x = rand_spawn.get_int(32, MAX_X);
    int spawn_y = rand_spawn.get_int(MIN_Y, MAX_Y);

    return bn::fixed_point(spawn_x, spawn_y);
}

}