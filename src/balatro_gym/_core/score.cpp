#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>

#include "balatro/src/score.hpp"

namespace nb = nanobind;
using namespace nb::literals;

void bind_score(nb::module_ &m) {
    m.def("score_cards", &Balatro::score_cards, "Score a collection of cards");
    m.def("calculate_table", &Balatro::calculate_table, "Calculate scoring table");
} 