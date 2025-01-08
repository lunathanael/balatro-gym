#include "types.hpp"
#include "io.hpp"
#include "hand.hpp"
#include "gamestate.hpp"
#include "score.hpp"


#include <iostream>
#include <random>
#include <list>
#include <array>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <numeric>
#include <cstring>


using namespace std;
using namespace Balatro;


int main() {
    uint64_t score_sum = 0;
    for(int i = 0; i < 100'000; ++i)
    {
        GameState game;
        game.play((1<<5) - 1);
        score_sum += game.score;
    }
    cout << static_cast<double>(score_sum) / 100'000 << endl;
    return 0;
}