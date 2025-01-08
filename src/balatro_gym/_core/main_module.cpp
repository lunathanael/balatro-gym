#include <nanobind/nanobind.h>

namespace nb = nanobind;

void bind_types(nb::module_ &m);

NB_MODULE(_core, m) {
    bind_types(m);
}