#include <ostream>
#include "Board.h"

using namespace bit;
/*
template<Alliance> int min();
template<Alliance> int max();

template<Alliance A>
int chooseMove(Board* const b) {
    int bestMove;
    int maxScore = INT32_MIN;
    int minScore = INT32_MAX;
    for(int i = 0; i < 9; ++i) {
        b->mark<A>(i);
        if(A == X) {
            max(b);
        }
        else {
            min(b);
        }
        b->mark<A>(i);
    }
}

template<Alliance A>
int miniMax(Board* const b,
            const int depth,
            const bool isMax) {

    if(b->hasVictory<X>()) return depth ;
    if(b->hasVictory<O>()) return
    if(b->isFull()) return 0;
}*/

constexpr bool hasVictory(const uint64_t t) {
    // Get the magic constant that corresponds to
    // this board and intersect with a mask
    // with a single high bit at an index based on
    // this board. The resulting sixty-four bit
    // number will either be zero or a non-negative
    // integer.
    return (Magic[t >> 3U] & (1U << (t & 7U)));
}

int main() {
    Board b;
    b.mark<X, 1>();
    b.mark<O, 8>();
    b.mark<X, 0>();
    b.mark<X, 2>();
    std::cout << b;
    std::cout << b.hasVictory<X>();
    b.mark<X, 2>();
    std::cout << b;
    std::cout << b.hasVictory<X>();
    std::cout << b.isFull();
    b.mark<X, 2>();
    b.mark<O, 3>();
    b.mark<X, 4>();
    b.mark<X, 5>();
    b.mark<O, 6>();
    b.mark<X, 7>();
    std::cout << b;
    std::cout << b.isFull();

    std::cout << '\n';

    constexpr Alliance f = X, q = ~f;

    std::cout << AllianceToChar[~q];
    std::cout << AllianceToChar[q];
    return 0;
}
