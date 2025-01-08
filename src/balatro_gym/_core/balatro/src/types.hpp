#ifndef TYPES_HPP_INCLUDED
#define TYPES_HPP_INCLUDED

#include <cstdint>

namespace Balatro {

enum class Suit : int8_t {
    Diamonds,
    Clubs,
    Hearts,
    Spades,
    NUMBER_OF_SUITS,
    NO_SUIT = -1,
};

enum class Rank : int8_t {
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
    NUMBER_OF_RANKS,
    NO_RANK = -1,
};

class Card {
   public:
    constexpr Card() : rank(Rank::NO_RANK), suit(Suit::NO_SUIT) {}
    constexpr Card(const Rank r, const Suit s) :
        rank(r),
        suit(s) {}

    constexpr Card(const int16_t card) :
        rank(static_cast<Rank>(card / static_cast<int16_t>(Suit::NUMBER_OF_SUITS))),
        suit(static_cast<Suit>(card % static_cast<int16_t>(Suit::NUMBER_OF_SUITS))) {}

    constexpr operator int16_t() const {
        return static_cast<int16_t>(suit)
             + static_cast<int16_t>(rank) * static_cast<int16_t>(Suit::NUMBER_OF_SUITS);
    }

    // Data members
    Rank rank;
    Suit suit;
};

namespace {
#define DEFINE_CARD(rank, suit) static constexpr const Card rank##Of##suit{Rank::rank, Suit::suit};
#define DEFINE_SUIT(suit) \
    DEFINE_CARD(Ace, suit) \
    DEFINE_CARD(Two, suit) \
    DEFINE_CARD(Three, suit) \
    DEFINE_CARD(Four, suit) \
    DEFINE_CARD(Five, suit) \
    DEFINE_CARD(Six, suit) \
    DEFINE_CARD(Seven, suit) \
    DEFINE_CARD(Eight, suit) \
    DEFINE_CARD(Nine, suit) \
    DEFINE_CARD(Ten, suit) \
    DEFINE_CARD(Jack, suit) \
    DEFINE_CARD(Queen, suit) \
    DEFINE_CARD(King, suit)

namespace Cards {
DEFINE_SUIT(Clubs)
DEFINE_SUIT(Diamonds)
DEFINE_SUIT(Hearts)
DEFINE_SUIT(Spades)
static constexpr const Card No_Card{Rank::NO_RANK, Suit::NO_SUIT};

}  // namespace Cards

#undef DEFINE_CARD
#undef DEFINE_SUIT

}

}  // namespace Balatro

#endif