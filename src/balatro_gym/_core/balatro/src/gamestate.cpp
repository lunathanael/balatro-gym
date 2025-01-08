#include "gamestate.hpp"
#include "score.hpp"

#include <random>
#include <algorithm>
#include <cassert>
#include <vector>

namespace {
    static constexpr const int NUMBER_OF_HANDS = 4;
    static constexpr const int NUMBER_OF_DISCARDS = 4;
}

namespace Balatro {

GameState::GameState(unsigned int seed) :
    score{0}, hands{NUMBER_OF_HANDS}, discards{NUMBER_OF_DISCARDS} {
    std::mt19937            g(seed);
    std::array<int16_t, 52> temp = DEFAULT_DECK_INDEXES;
    std::shuffle(temp.begin(), temp.end(), g);
    deck = std::vector<Card>(temp.begin(), temp.end());

    hand = {{deck[51], deck[50], deck[49], deck[48], deck[47], deck[46], deck[45], deck[44]}};

    deck.resize(deck.size() - 8);
}

GameState::GameState() :
    score{0}, hands{NUMBER_OF_HANDS}, discards{NUMBER_OF_DISCARDS} {
    std::random_device      rd;
    std::mt19937            g(rd());
    std::array<int16_t, 52> temp = DEFAULT_DECK_INDEXES;
    std::shuffle(temp.begin(), temp.end(), g);
    deck = std::vector<Card>(temp.begin(), temp.end());

    hand = Hand{{deck[51], deck[50], deck[49], deck[48], deck[47], deck[46], deck[45], deck[44]}};

    deck.resize(deck.size() - 8);
}

int GameState::play(int action) {
    assert((action > 0 && action <= 5 && action < (1 << 8)) && "invalid move");
    assert(hands > 0 && "no hands left");
    
    std::vector<Card> played_cards;
    
    int i = 0;
    while(action)
    {
        int bit = action & 1;
        action >>= 1;
        if (bit)
        {
            played_cards.push_back(hand[i]);
            if (deck.empty())
            {
                hand[i] = Cards::No_Card;
            }
            else
            {
                hand[i] = deck.back();
                deck.pop_back();
            }
        }
        i++;
    }

    hand.sort();
    --hands;
    int added_score = score_cards(played_cards);
    score += added_score;
    return added_score;
}

void GameState::discard(int action) {
    assert((action > 0 && action <= 5 && action < (1 << 8)) && "invalid move");
    assert(discards > 0 && "no discards left");
    int i = 0;
    while(action)
    {
        int bit = action & 1;
        action >>= 1;
        if (bit)
        {
            if (deck.empty())
            {
                hand[i] = Cards::No_Card;
            }
            else
            {
                hand[i] = deck.back();
                deck.pop_back();
            }
        }
        i++;
    }

    hand.sort();
    --discards;
}

bool GameState::is_terminal() const {
    return (hands == 0) || (hand[0] == Cards::No_Card);
}

}