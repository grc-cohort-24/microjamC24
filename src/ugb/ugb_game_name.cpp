#include "ugb/ugb_game_name.h"

namespace ugb {
    ugb::ugb_game_name::ugb_game_name([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data& data) : mj::game("ugb") {

    }

    bn::string<16> title() {
        return "UGB_Game";
    }

    int total_frames() {
        return 600; // 10 seconds
    }

    bool victory() {
        return false;
    }

    mj::game_result play([[maybe_unused]] const mj::game_data& data) {
        mj::game_result result(victory(), false);
        return result;
    }

    void fade_in([[maybe_unused]] const mj::game_data &data) {

    }

    void fade_out([[maybe_unused]] const mj::game_data &data) {

    }

}