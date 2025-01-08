#ifndef SCORE_HPP_INCLUDED
#define SCORE_HPP_INCLUDED

#include "types.hpp"

#include <vector>

namespace Balatro {

int score_cards(const std::vector<Card>& cards);
void calculate_table();

}

#endif