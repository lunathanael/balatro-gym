#include <nanobind/nanobind.h>
#include <nanobind/stl/bind_vector.h>
#include <nanobind/stl/array.h>

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
        .value("NO_SUIT", Balatro::Suit::NO_SUIT);

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
        .value("NO_RANK", Balatro::Rank::NO_RANK);

    // Binding the Card class
    nb::class_<Balatro::Card>(m, "Card")
        .def(nb::init<>())  // Default constructor
        .def(nb::init<Balatro::Rank, Balatro::Suit>())  // Constructor with rank and suit
        .def(nb::init<int16_t>())  // Constructor with int16_t
        .def("__int__", &Balatro::Card::operator int16_t)  // Conversion to int16_t
        .def_rw("rank", &Balatro::Card::rank)  // Expose rank
        .def_rw("suit", &Balatro::Card::suit);  // Expose suit
}