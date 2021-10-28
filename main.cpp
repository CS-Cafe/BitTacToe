#include <ostream>
#include "Board.h"

using namespace bit;
using std::cout;

namespace opponent {

    template<bool>
    int AlphaOmega(Board*, int, int, int);

    constexpr int HIGH_SCORE = 10;

    /**
     * Opponent
     *
     * <p>
     * This Tic-Tac-Toe opponent uses miniMax to calculate the best move.
     * Minimax is a search algorithm capable of choosing optimal moves in a zero-sum
     * game. A zero-sum game is one in which the respective gains and losses of the
     * two players (or teams) cancel each other out. This property ensures that a
     * loss for one player results in an equivalent gain for the other.
     *
     * <p>
     * The goal of minimax is to choose a move which minimizes the maximum loss
     * for the current player. The two players present in the game are designated
     * maximizer and minimizer and a sub-tree is created for each of the current
     * player's legal moves. At each level of recursion, the current player
     * alternates. at each node, all legal moves are tried out individually. When
     * the algorithm reaches a terminal node, the board is evaluated and scored,
     * and this score is returned up the tree. Each internal node selects only the
     * best score for its current player (minimum for minimizer, maximum for
     * maximizer). In this way, a single score is propagated back up each tree to
     * represent each of the initiating player's moves. Here, the highest-scoring
     * move is chosen for the initiating player. This process ensures that only
     * the wort-case scenario is considered for the initiating player-- A very
     * smart opponent.
     *
     * <p>
     * This minimax algorithm uses alpha-beta pruning to cut off large portions of
     * the search tree that need not be visited. If a part of the tree is guaranteed
     * to be cut off by a min or max node, then there is no need to look any further.
     * We can make this guarantee by setting the values of variables 'alpha' and 'beta'
     * as a score is returned from a child node up into a parent node. This process
     * relies on the fact that each search tree is navigated both iteratively and
     * recursively. For Example, after returning from a child min-node into a parent
     * max-node, alpha is set, and the algorithm enters the next child min-node. The
     * value that this min-node returns must be between alpha and beta. Beta is now
     * set during the execution of the min-node. If beta is less than alpha (since
     * this is a min-node), it will be impossible to find a value that is both greater
     * than alpha and less than beta. At this point, there is no need to continue
     * searching past this node, so we simply return beta.
     */
    int chooseMove(Board *const b) {
        int bestMove = -1,
            maxScore = INT8_MIN,
            currentScore;
        for (int i = 0; i < BoardLength; ++i) {
            if (b->fullSquare(i)) continue;
            b->mark<X>(i);
            currentScore =
                AlphaOmega<false>(
                    b, 0,
                    INT8_MIN, INT8_MAX
                );
            b->mark<X>(i);
            if (currentScore > maxScore) {
                maxScore = currentScore;
                bestMove = i;
            }
        }
        return bestMove;
    }

    template<bool MAX>
    int AlphaOmega(Board *const b,
                   const int depth,
                   int a,
                   int o) {

        // Maximizer (computer) wins.
        if (b->hasVictory<X>())
            return HIGH_SCORE - depth;
        // Minimizer (user) wins.
        if (b->hasVictory<O>())
            return depth - HIGH_SCORE;
        // Tie !
        if (b->isFull()) return 0;

        int score = MAX? INT8_MIN: INT8_MAX;
        for (int i = 0; i < BoardLength; ++i) {
            if (b->fullSquare(i))
                continue;
            if(MAX) {
                b->mark<X>(i);
                score = std::max(score,
                    AlphaOmega<false>(
                        b, depth + 1,
                        a, o
                    )
                );
                b->mark<X>(i);
                a = score;
            } else {
                b->mark<O>(i);
                score = std::min(score,
                    AlphaOmega<true>(
                        b, depth + 1,
                        a, o
                    )
                );
                b->mark<O>(i);
                o = score;
            }
            if (a >= o) return score;
        }
        return score;
    }
}

int main() {
    Board b; char c; int i = -1; bool x, o;
    do {
        c = ' ';
        while(!b.isFull() &&
              !(x = b.hasVictory<X>()) &&
              !(o = b.hasVictory<O>())) {
            std::cout << "\nMake a move (0-8)\n"
                      << "8 7 6\n"
                      << "5 4 3\n"
                      << "2 1 0\n>>_";
            scanf("%d", &i);
            if(i < 0 || i > 8 || b.fullSquare(i))
                continue;
            b.mark<O>(i);
            std::cout << "\nYour move:\n" << b << '\n';
            if(b.isFull()) break;
            b.mark<X>(opponent::chooseMove(&b));
            std::cout << "My move:\n" << b << '\n';
        }
        std::cout << '\n'
                  << (x? "I win!":
                      o? "You win!":
                         "Tie!")
                  << "\nplay again? (y/n)\n>>_";
        b.reset();
        scanf("%c", &c);
        scanf("%c", &c);
    } while(c == 'y');
    return 0;
}
