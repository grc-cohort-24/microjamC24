#include <bn_math.h>

#include "ugb/ugb_entity_manager.h"
#include "ugb/ugb_constants.h"
#include "ugb/ugb_state.h"

namespace ugb {

    bn::fixed_point get_safe_spawn_loc(bn::random random) {
        bn::fixed spawn_x, spawn_y, dx, dy;
        bn::fixed_point spawn_point(constants::MAX_X, 0);

        for (int i = 0; i < constants::spawn::MAX_ATTEMPTS; i++) {
            bool safe = true;
            // Choose a spawn location within the screen bounds (+ padding so the sprite stays on screen)
            spawn_x = random.get_unbiased_fixed(constants::spawn::MIN_X, constants::spawn::MAX_X);
            spawn_y = random.get_unbiased_fixed(constants::spawn::MIN_Y, constants::spawn::MAX_Y);

            for (Entity entity : state::entities) {
                dx = bn::abs(spawn_x - entity.x());
                dy = bn::abs(spawn_y - entity.y());
                if (dx < constants::spawn::MIN_DISTANCE || dy < constants::spawn::MIN_DISTANCE) {
                    safe = false;
                    break;
                }
            }
            if (safe) {
                spawn_point.set_x(spawn_x);
                spawn_point.set_y(spawn_y);
                break;
            }
        }
        return spawn_point;
    }
}