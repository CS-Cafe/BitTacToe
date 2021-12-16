# Unreasonably Fast Tic Tac Toe
 
#### *A fast tic tac toe project.*

## *Command Line Interface*

<pre>
 <code>
        x | o | o
       ---+---+---
        - | x | -
       ---+---+---
        - | - | -
       I took 0.000001 seconds!
       Make a move (1-9)
       9 8 7
       6 5 4
       3 2 1
       >>_
 </code>
</pre>

## *Perfect Play*

<p>
A perfect-play tic tac toe engine plays a game with no errors. The game will never result in a
win for the user. This engine is based around Turing's Minimax algorithm. 
</p> 

## *Compact Bit Board Representation*

<p>
The game of tic tac toe is played on a board with nine squares. This conveniently allows us
to represent the board with two 16-bit integers (four bytes). Marking and erasing a move on
the board can be accomplished with xor. Tie checking can be accomplished with a simple equality
check. Victory checking is a matter of mapping one layer of the board to a single bit in a 
magic table.
</p> 

## *Unparalleled Speed (for now)*
<p>
Due to its extremely small state-space, the full game tree of tic tac toe can be explored in 
a matter of microseconds. This speed allows for full exploration of the "perfect play" tree 
in well under a second. The perfect play tree can be used to create a table of perfect moves.
These perfect moves are now precalculated at startup and stored in a 12288 byte table with a 
quadratic "open-address" hash scheme.
</p>

<p>
I think that this can be improved with perfect hashing. 
However, I was unable to find a multiplier. If you can find a multiplier, please
let me know and I'll add you to the project!
</p>

## *Average runtime of DFS from home position: 1 microsecond.*

