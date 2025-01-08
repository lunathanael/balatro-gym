#ifndef HAND_HPP_INCLUDED
#define HAND_HPP_INCLUDED

#include "types.hpp"

#include <array>
#include <iterator>

namespace Balatro {

class Hand {
   public:
    static constexpr const size_t size = 8;

    constexpr Hand() :
        cards{} {}
    constexpr Hand(const std::array<Card, size>& _cards) :
        cards(_cards) {}
    void                  sort();
    constexpr const Card& operator[](std::size_t i) const { return cards[i]; }
    constexpr Card&       operator[](std::size_t i) { return cards[i]; }
    constexpr auto begin() { return cards.begin(); }
    constexpr auto end() { return cards.end(); }
    constexpr auto begin() const { return cards.begin(); }
    constexpr auto end() const { return cards.end(); }
    constexpr auto cbegin() const { return cards.cbegin(); }
    constexpr auto cend() const { return cards.cend(); }

    // Data members
    std::array<Card, 8> cards;
};

}

#endif