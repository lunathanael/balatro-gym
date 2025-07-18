#include <nanobind/nanobind.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/string.h>
#include <nanobind/make_iterator.h>
#include <sstream>

#include "balatro/src/hand.hpp"
#include "balatro/src/io.hpp"

namespace nb = nanobind;
using namespace nb::literals;

void bind_hand(nb::module_ &m) {
    nb::class_<Balatro::Hand>(m, "Hand")
        .def_ro_static("size", &Balatro::Hand::size)  // Expose static size constant
        .def(nb::init<>())  // Default constructor
        .def(nb::init<const std::array<Balatro::Card, 8>&>())  // Constructor with cards array
        .def("sort", &Balatro::Hand::sort)  // Sort method
        .def("__getitem__", [](const Balatro::Hand &h, size_t i) { return h[i]; })  // [] operator
        .def("__setitem__", [](Balatro::Hand &h, size_t i, const Balatro::Card &card) { h[i] = card; })  // [] operator
        .def_rw("cards", &Balatro::Hand::cards)  // Expose cards array
        .def("__repr__", [](const Balatro::Hand& hand) {
            std::stringstream ss;
            ss << hand;
            return ss.str();
        })  // Add string representation for Python
        .def("__iter__",
                [](const Balatro::Hand &v) {
                    return nb::make_iterator(nb::type<Balatro::Hand>(), "iterator",
                                            v.begin(), v.end());
                }, nb::keep_alive<0, 1>());
} 