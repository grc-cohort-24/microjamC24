#include "bar/bar_spawn_coin.h"

namespace bar
{

    void bar_spawn_coin(bn::vector<bar_coin, MAX_COINS> &coins, bn::fixed x_start, bn::fixed y_start, bn::fixed base_speed, bn::size coin_size)
    {
        if (coins.size() < MAX_COINS)
        {
            bar_coin coin = bar_coin(x_start, y_start, base_speed, coin_size);
            coins.push_back(coin);
        }
    }

}