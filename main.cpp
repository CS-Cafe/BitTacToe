#include <ostream>
#include "Board.h"
#include "Opponent.h"

using namespace bit;
using namespace opponent;
using std::cout;
using std::cin;
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
            if(b.isFull()) break;
            b.mark<X>(opponent::chooseMove(&b));
            cout << "\033[2J\033[H" << flush;
            cout << b;
        }
        cout << '\n'
                  << (x? "I win!":
                      o? "You win!":
                         "Tie!")
                  << "\nplay again? (y/n)\n>>_";
        b.reset();
        while(!(cin >> c)) {
            cin.clear();
            cin.ignore(INT32_MAX,'\n');
        }
    } while(c == 'y');
    return 0;
}
