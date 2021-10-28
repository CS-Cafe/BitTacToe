#include <ostream>
#include "Board.h"
#include "Opponent.h"

using namespace bit;
using namespace opponent;
using std::cout;
using std::flush;

/**
 * I wrote this in 5 minutes... It needs lots of
 * work. A GUI would be awesome!
 *
 * @return
 */
int main() {
    Board b; char c; int i = -1; bool x, o;
    do {
        std::cout << "\033[2J\033[H" << flush;
        std::cout << b;
        while(!b.isFull() &&
              !(x = b.hasVictory<X>()) &&
              !(o = b.hasVictory<O>())) {
            std::cout << "\nMake a move (0-8)\n"
                      << "8 7 6\n"
                      << "5 4 3\n"
                      << "2 1 0\n>>_";
            scanf("%d", &i);
            if(i < 0 || i > 8 || b.occupiedSquare(i))
                continue;
            b.mark<O>(i);
            if(b.isFull()) break;
            b.mark<X>(opponent::chooseMove(&b));
            std::cout << "\033[2J\033[H" << flush;
            std::cout << b;
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
