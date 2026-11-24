#pragma once

#include <bn_vector.h>

#include "bar/bar_coin.h"
#include "bar/bar_player.h"
#include "bar_constants.h"

namespace bar {

    void bar_spawn_coin(bn::vector<bar_coin, MAX_COINS> &coins, bn::fixed x_start, bn::fixed y_start, bn::fixed base_speed, bn::size coin_size);

}