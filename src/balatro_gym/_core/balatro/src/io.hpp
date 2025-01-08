#ifndef IO_HPP_INCLUDED
#define IO_HPP_INCLUDED

#include "types.hpp"
#include "hand.hpp"

#include <ostream>

namespace Balatro {
inline std::ostream& operator<<(std::ostream& os, const Suit& suit) {
    switch (suit)
    {
    case Suit::Spades :
        return os << "♠";
    case Suit::Hearts :
        return os << "♥";
    case Suit::Diamonds :
        return os << "♦";
    case Suit::Clubs :
        return os << "♣";
    default :
        return os << "?";
    }
}

inline std::ostream& operator<<(std::ostream& os, const Rank& rank) {
    switch (rank)
    {
    case Rank::Ace :
        return os << "A";
    case Rank::Two :
        return os << "2";
    case Rank::Three :
        return os << "3";
    case Rank::Four :
        return os << "4";
    case Rank::Five :
        return os << "5";
    case Rank::Six :
        return os << "6";
    case Rank::Seven :
        return os << "7";
    case Rank::Eight :
        return os << "8";
    case Rank::Nine :
        return os << "9";
    case Rank::Ten :
        return os << "10";
    case Rank::Jack :
        return os << "J";
    case Rank::Queen :
        return os << "Q";
    case Rank::King :
        return os << "K";
    default :
        return os << "?";
    }
}

inline std::ostream& operator<<(std::ostream& os, const Card& card) {
    return os << card.suit << card.rank;
}

inline std::ostream& operator<<(std::ostream& os, const Hand& hand) {
    for (const auto& card : hand.cards)
    {
        os << card << " ";
    }
    return os;
}

}  // namespace Balatro


#endif