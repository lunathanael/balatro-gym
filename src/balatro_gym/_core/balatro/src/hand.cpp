#include "hand.hpp"

#include <algorithm>
#include <array>


namespace Balatro {

void Hand::sort() {
#define CMP_SWAP(arr, i, j) \
    if (arr[i] < arr[j]) \
        std::swap(arr[i], arr[j]);

    std::array<int16_t, 8> temp = {static_cast<int16_t>(cards[0]), static_cast<int16_t>(cards[1]),
                                   static_cast<int16_t>(cards[2]), static_cast<int16_t>(cards[3]),
                                   static_cast<int16_t>(cards[4]), static_cast<int16_t>(cards[5]),
                                   static_cast<int16_t>(cards[6]), static_cast<int16_t>(cards[7])};

    CMP_SWAP(temp, 0, 1);
    CMP_SWAP(temp, 2, 3);
    CMP_SWAP(temp, 4, 5);
    CMP_SWAP(temp, 6, 7);
    CMP_SWAP(temp, 0, 2);
    CMP_SWAP(temp, 1, 3);
    CMP_SWAP(temp, 4, 6);
    CMP_SWAP(temp, 5, 7);
    CMP_SWAP(temp, 1, 2);
    CMP_SWAP(temp, 5, 6);
    CMP_SWAP(temp, 0, 4);
    CMP_SWAP(temp, 1, 5);
    CMP_SWAP(temp, 2, 6);
    CMP_SWAP(temp, 3, 7);
    CMP_SWAP(temp, 2, 4);
    CMP_SWAP(temp, 3, 5);
    CMP_SWAP(temp, 1, 2);
    CMP_SWAP(temp, 3, 4);
    CMP_SWAP(temp, 5, 6);

    cards = {Card(temp[0]), Card(temp[1]), Card(temp[2]), Card(temp[3]),
             Card(temp[4]), Card(temp[5]), Card(temp[6]), Card(temp[7])};

#undef CMP_SWAP
}

}