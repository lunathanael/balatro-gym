#include <nanobind/nanobind.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/bind_vector.h>
#include <nanobind/stl/string.h>
#include <sstream>
#include <string>

#include "balatro/src/io.hpp"
#include "balatro/src/types.hpp"

namespace nb = nanobind;
using namespace nb::literals;

void bind_types(nb::module_ &m) {
  // Binding the Suit enum
  nb::enum_<Balatro::Suit>(m, "Suit")
      .value("Diamonds", Balatro::Suit::Diamonds)
      .value("Clubs", Balatro::Suit::Clubs)
      .value("Hearts", Balatro::Suit::Hearts)
      .value("Spades", Balatro::Suit::Spades)
      .value("NUMBER_OF_SUITS", Balatro::Suit::NUMBER_OF_SUITS)
      .value("NO_SUIT", Balatro::Suit::NO_SUIT)
      .def("__repr__",
           [](const Balatro::Suit &suit) {
             std::stringstream ss;
             ss << suit;
             return ss.str();
           })
      .def("__int__",
           [](const Balatro::Suit &suit) { return static_cast<int>(suit); });

  // Binding the Rank enum
  nb::enum_<Balatro::Rank>(m, "Rank")
      .value("Two", Balatro::Rank::Two)
      .value("Three", Balatro::Rank::Three)
      .value("Four", Balatro::Rank::Four)
      .value("Five", Balatro::Rank::Five)
      .value("Six", Balatro::Rank::Six)
      .value("Seven", Balatro::Rank::Seven)
      .value("Eight", Balatro::Rank::Eight)
      .value("Nine", Balatro::Rank::Nine)
      .value("Ten", Balatro::Rank::Ten)
      .value("Jack", Balatro::Rank::Jack)
      .value("Queen", Balatro::Rank::Queen)
      .value("King", Balatro::Rank::King)
      .value("Ace", Balatro::Rank::Ace)
      .value("NUMBER_OF_RANKS", Balatro::Rank::NUMBER_OF_RANKS)
      .value("NO_RANK", Balatro::Rank::NO_RANK)
      .def("__repr__",
           [](const Balatro::Rank &rank) {
             std::stringstream ss;
             ss << rank;
             return ss.str();
           })
      .def("__int__",
           [](const Balatro::Rank &rank) { return static_cast<int>(rank); });

  // Binding the Card class
  nb::class_<Balatro::Card>(m, "Card")
      .def(nb::init<>()) // Default constructor
      .def(nb::init<Balatro::Rank,
                    Balatro::Suit>()) // Constructor with rank and suit
      .def(nb::init<int16_t>())       // Constructor with int16_t
      .def("__int__", &Balatro::Card::operator int16_t) // Conversion to int16_t
      .def_rw("rank", &Balatro::Card::rank)             // Expose rank
      .def_rw("suit", &Balatro::Card::suit)             // Expose suit
      .def("__repr__", [](const Balatro::Card &card) {
        std::stringstream ss;
        ss << card;
        return ss.str();
      }); // Add string representation for Python

  // Create a submodule for cards
  auto cards = m.def_submodule("Cards", "Predefined card constants");

  // Define all card constants in the submodule
  cards.attr("AceOfClubs") = Balatro::Cards::AceOfClubs;
  cards.attr("TwoOfClubs") = Balatro::Cards::TwoOfClubs;
  cards.attr("ThreeOfClubs") = Balatro::Cards::ThreeOfClubs;
  cards.attr("FourOfClubs") = Balatro::Cards::FourOfClubs;
  cards.attr("FiveOfClubs") = Balatro::Cards::FiveOfClubs;
  cards.attr("SixOfClubs") = Balatro::Cards::SixOfClubs;
  cards.attr("SevenOfClubs") = Balatro::Cards::SevenOfClubs;
  cards.attr("EightOfClubs") = Balatro::Cards::EightOfClubs;
  cards.attr("NineOfClubs") = Balatro::Cards::NineOfClubs;
  cards.attr("TenOfClubs") = Balatro::Cards::TenOfClubs;
  cards.attr("JackOfClubs") = Balatro::Cards::JackOfClubs;
  cards.attr("QueenOfClubs") = Balatro::Cards::QueenOfClubs;
  cards.attr("KingOfClubs") = Balatro::Cards::KingOfClubs;

  cards.attr("AceOfDiamonds") = Balatro::Cards::AceOfDiamonds;
  cards.attr("TwoOfDiamonds") = Balatro::Cards::TwoOfDiamonds;
  cards.attr("ThreeOfDiamonds") = Balatro::Cards::ThreeOfDiamonds;
  cards.attr("FourOfDiamonds") = Balatro::Cards::FourOfDiamonds;
  cards.attr("FiveOfDiamonds") = Balatro::Cards::FiveOfDiamonds;
  cards.attr("SixOfDiamonds") = Balatro::Cards::SixOfDiamonds;
  cards.attr("SevenOfDiamonds") = Balatro::Cards::SevenOfDiamonds;
  cards.attr("EightOfDiamonds") = Balatro::Cards::EightOfDiamonds;
  cards.attr("NineOfDiamonds") = Balatro::Cards::NineOfDiamonds;
  cards.attr("TenOfDiamonds") = Balatro::Cards::TenOfDiamonds;
  cards.attr("JackOfDiamonds") = Balatro::Cards::JackOfDiamonds;
  cards.attr("QueenOfDiamonds") = Balatro::Cards::QueenOfDiamonds;
  cards.attr("KingOfDiamonds") = Balatro::Cards::KingOfDiamonds;

  cards.attr("AceOfHearts") = Balatro::Cards::AceOfHearts;
  cards.attr("TwoOfHearts") = Balatro::Cards::TwoOfHearts;
  cards.attr("ThreeOfHearts") = Balatro::Cards::ThreeOfHearts;
  cards.attr("FourOfHearts") = Balatro::Cards::FourOfHearts;
  cards.attr("FiveOfHearts") = Balatro::Cards::FiveOfHearts;
  cards.attr("SixOfHearts") = Balatro::Cards::SixOfHearts;
  cards.attr("SevenOfHearts") = Balatro::Cards::SevenOfHearts;
  cards.attr("EightOfHearts") = Balatro::Cards::EightOfHearts;
  cards.attr("NineOfHearts") = Balatro::Cards::NineOfHearts;
  cards.attr("TenOfHearts") = Balatro::Cards::TenOfHearts;
  cards.attr("JackOfHearts") = Balatro::Cards::JackOfHearts;
  cards.attr("QueenOfHearts") = Balatro::Cards::QueenOfHearts;
  cards.attr("KingOfHearts") = Balatro::Cards::KingOfHearts;

  cards.attr("AceOfSpades") = Balatro::Cards::AceOfSpades;
  cards.attr("TwoOfSpades") = Balatro::Cards::TwoOfSpades;
  cards.attr("ThreeOfSpades") = Balatro::Cards::ThreeOfSpades;
  cards.attr("FourOfSpades") = Balatro::Cards::FourOfSpades;
  cards.attr("FiveOfSpades") = Balatro::Cards::FiveOfSpades;
  cards.attr("SixOfSpades") = Balatro::Cards::SixOfSpades;
  cards.attr("SevenOfSpades") = Balatro::Cards::SevenOfSpades;
  cards.attr("EightOfSpades") = Balatro::Cards::EightOfSpades;
  cards.attr("NineOfSpades") = Balatro::Cards::NineOfSpades;
  cards.attr("TenOfSpades") = Balatro::Cards::TenOfSpades;
  cards.attr("JackOfSpades") = Balatro::Cards::JackOfSpades;
  cards.attr("QueenOfSpades") = Balatro::Cards::QueenOfSpades;
  cards.attr("KingOfSpades") = Balatro::Cards::KingOfSpades;

  cards.attr("No_Card") = Balatro::Cards::No_Card;


}