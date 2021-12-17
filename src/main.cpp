#include <ostream>
#include <ctime>
#include "Board.h"
#include "PerfectPlay.h"

using namespace bit;
using namespace perf;
using std::cout, std::cin, std::flush;

/**
 * Tic Tac Toe
 */
int main() {
    Board b; char c; int i = -1; bool x, o;
    uint16_t hash = 0;
    do {
        cout << "\033[2J\033[H" << flush;
        cout << b;
        while(!b.isFull() &&
              !(x = b.hasVictory<X>()) &&
              !(o = b.hasVictory<O>())) {
            cout << "\nMake a move (1-9)\n"
                      << "9 8 7\n"
                      << "6 5 4\n"
                      << "3 2 1\n>>_";
            while(!(cin >> i)) {
                cin.clear();
                cin.ignore(INT32_MAX,'\n');
            }
            if(i < 1 || i > 9 || b.occupiedSquare(i - 1))
                continue;
            b.mark<O>(i - 1);
            hash ^= zobrist<O>(9 - i);
            if(b.isFull()) break;
            const long start = clock();
            const int m = probe(hash);
            b.mark<X>(m);
            const long end = clock() - start;
            hash ^= zobrist<X>(8 - m);
            cout << "\033[2J\033[H" << flush;
            cout << b;
            printf(
                "I took %.6f seconds!",
                ((double)end) / CLOCKS_PER_SEC
            );
        }
        cout << '\n'
             << (x? "I win!":
                 o? "You win!":
                    "Tie!")
             << "\nplay again? (y/n)\n>>_";
        b.reset();
        hash = 0;
        while(!(cin >> c)) {
            cin.clear();
            cin.ignore(INT32_MAX,'\n');
        }
    } while(c == 'y');
    return 0;
}
