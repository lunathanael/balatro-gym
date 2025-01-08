#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "types.hpp"
#include "hand.hpp"

#include <array>
#include <vector>

namespace Balatro {

class GameState {
   public:
    GameState();
    GameState(unsigned int seed);
    int play(int action);
    void discard(int action);
    bool is_terminal() const;

    // Data members
    std::vector<Card> deck;
    Hand              hand;
    int score;
    int hands;
    int discards;
};


constexpr const std::array<const Card, 52> DEFAULT_DECK = {
  Cards::AceOfSpades,   Cards::TwoOfSpades,     Cards::ThreeOfSpades,   Cards::FourOfSpades,
  Cards::FiveOfSpades,  Cards::SixOfSpades,     Cards::SevenOfSpades,   Cards::EightOfSpades,
  Cards::NineOfSpades,  Cards::TenOfSpades,     Cards::JackOfSpades,    Cards::QueenOfSpades,
  Cards::KingOfSpades,  Cards::AceOfClubs,      Cards::TwoOfClubs,      Cards::ThreeOfClubs,
  Cards::FourOfClubs,   Cards::FiveOfClubs,     Cards::SixOfClubs,      Cards::SevenOfClubs,
  Cards::EightOfClubs,  Cards::NineOfClubs,     Cards::TenOfClubs,      Cards::JackOfClubs,
  Cards::QueenOfClubs,  Cards::KingOfClubs,     Cards::AceOfHearts,     Cards::TwoOfHearts,
  Cards::ThreeOfHearts, Cards::FourOfHearts,    Cards::FiveOfHearts,    Cards::SixOfHearts,
  Cards::SevenOfHearts, Cards::EightOfHearts,   Cards::NineOfHearts,    Cards::TenOfHearts,
  Cards::JackOfHearts,  Cards::QueenOfHearts,   Cards::KingOfHearts,    Cards::AceOfDiamonds,
  Cards::TwoOfDiamonds, Cards::ThreeOfDiamonds, Cards::FourOfDiamonds,  Cards::FiveOfDiamonds,
  Cards::SixOfDiamonds, Cards::SevenOfDiamonds, Cards::EightOfDiamonds, Cards::NineOfDiamonds,
  Cards::TenOfDiamonds, Cards::JackOfDiamonds,  Cards::QueenOfDiamonds, Cards::KingOfDiamonds,
};

constexpr const std::array<int16_t, 52> DEFAULT_DECK_INDEXES = {
  static_cast<int16_t>(Cards::AceOfSpades),     static_cast<int16_t>(Cards::TwoOfSpades),
  static_cast<int16_t>(Cards::ThreeOfSpades),   static_cast<int16_t>(Cards::FourOfSpades),
  static_cast<int16_t>(Cards::FiveOfSpades),    static_cast<int16_t>(Cards::SixOfSpades),
  static_cast<int16_t>(Cards::SevenOfSpades),   static_cast<int16_t>(Cards::EightOfSpades),
  static_cast<int16_t>(Cards::NineOfSpades),    static_cast<int16_t>(Cards::TenOfSpades),
  static_cast<int16_t>(Cards::JackOfSpades),    static_cast<int16_t>(Cards::QueenOfSpades),
  static_cast<int16_t>(Cards::KingOfSpades),    static_cast<int16_t>(Cards::AceOfClubs),
  static_cast<int16_t>(Cards::TwoOfClubs),      static_cast<int16_t>(Cards::ThreeOfClubs),
  static_cast<int16_t>(Cards::FourOfClubs),     static_cast<int16_t>(Cards::FiveOfClubs),
  static_cast<int16_t>(Cards::SixOfClubs),      static_cast<int16_t>(Cards::SevenOfClubs),
  static_cast<int16_t>(Cards::EightOfClubs),    static_cast<int16_t>(Cards::NineOfClubs),
  static_cast<int16_t>(Cards::TenOfClubs),      static_cast<int16_t>(Cards::JackOfClubs),
  static_cast<int16_t>(Cards::QueenOfClubs),    static_cast<int16_t>(Cards::KingOfClubs),
  static_cast<int16_t>(Cards::AceOfHearts),     static_cast<int16_t>(Cards::TwoOfHearts),
  static_cast<int16_t>(Cards::ThreeOfHearts),   static_cast<int16_t>(Cards::FourOfHearts),
  static_cast<int16_t>(Cards::FiveOfHearts),    static_cast<int16_t>(Cards::SixOfHearts),
  static_cast<int16_t>(Cards::SevenOfHearts),   static_cast<int16_t>(Cards::EightOfHearts),
  static_cast<int16_t>(Cards::NineOfHearts),    static_cast<int16_t>(Cards::TenOfHearts),
  static_cast<int16_t>(Cards::JackOfHearts),    static_cast<int16_t>(Cards::QueenOfHearts),
  static_cast<int16_t>(Cards::KingOfHearts),    static_cast<int16_t>(Cards::AceOfDiamonds),
  static_cast<int16_t>(Cards::TwoOfDiamonds),   static_cast<int16_t>(Cards::ThreeOfDiamonds),
  static_cast<int16_t>(Cards::FourOfDiamonds),  static_cast<int16_t>(Cards::FiveOfDiamonds),
  static_cast<int16_t>(Cards::SixOfDiamonds),   static_cast<int16_t>(Cards::SevenOfDiamonds),
  static_cast<int16_t>(Cards::EightOfDiamonds), static_cast<int16_t>(Cards::NineOfDiamonds),
  static_cast<int16_t>(Cards::TenOfDiamonds),   static_cast<int16_t>(Cards::JackOfDiamonds),
  static_cast<int16_t>(Cards::QueenOfDiamonds), static_cast<int16_t>(Cards::KingOfDiamonds)};
}

#endif