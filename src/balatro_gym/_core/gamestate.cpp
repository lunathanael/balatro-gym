#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>

#include "balatro/src/gamestate.hpp"

namespace nb = nanobind;
using namespace nb::literals;

void bind_gamestate(nb::module_ &m) {
    nb::class_<Balatro::GameState>(m, "GameState")
        .def(nb::init<>())  // Default constructor
        .def(nb::init<unsigned int>())  // Constructor with seed
        .def("play", &Balatro::GameState::play)  // Play method
        .def("discard", &Balatro::GameState::discard)  // Discard method
        .def_rw("deck", &Balatro::GameState::deck)  // Expose deck
        .def_rw("hand", &Balatro::GameState::hand)  // Expose hand
        .def_rw("score", &Balatro::GameState::score)  // Expose score
        .def_rw("hands", &Balatro::GameState::hands)  // Expose hands count
        .def_rw("discards", &Balatro::GameState::discards)  // Expose discards count
        .def("is_terminal", &Balatro::GameState::is_terminal)  // Expose terminal state
        .def("__copy__", [](const Balatro::GameState &self) { return Balatro::GameState(self); });  // Expose copy method
} 