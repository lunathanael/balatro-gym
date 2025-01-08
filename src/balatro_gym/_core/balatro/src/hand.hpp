#ifndef HAND_HPP_INCLUDED
#define HAND_HPP_INCLUDED

#include "types.hpp"

#include <array>
#include <iterator>

namespace Balatro {

class Hand {
   public:
    constexpr Hand() : cards{} {}
    constexpr Hand(const std::array<Card, 8>& _cards) :
        cards(_cards) {}
    void                  sort();
    constexpr const Card& operator[](std::size_t i) const { return cards[i]; }
    constexpr Card&       operator[](std::size_t i) { return cards[i]; }

    // Data members
    std::array<Card, 8> cards;
};

}

#endif