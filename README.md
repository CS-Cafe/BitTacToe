# Unreasonably Fast Tic Tac Toe 

<h5><i>Faster than lightning - Faster than Zenitsu in REM.</i></h5>

"Yes. It's been done before. In fact, it's been done to death. Let's dare to pick the project
up one last time... And finish it." 

<h5><i>queue the epic music...</i></h5>

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
A perfect-play tic tac toe engine plays a game with no errors. The game will never yield a
win for the user. A perfect-play engine is based on the classical Minimax algorithm. This 
engine is a perfect-play engine.
</p> 

## *Compact Bit Board Representation*

<p>
The game of tic tac toe is played on a board with nine squares. This conveniently allows us
to represent the board with two 16-bit integers (four bytes). Marking and erasing a move on
the board is accomplished with xor. Tie checking is accomplished with a simple equality
check. Victory checking is a matter of mapping one layer of the board to a single bit in a 
magic table.
</p> 

## *Unparalleled Speed (for now)*

<p>
Due to its extremely small state-space, the full game tree of tic tac toe can be explored in 
a matter of microseconds. This speed allows for exploration of the entire "perfect-play" tree 
in well under a second. The perfect-play tree can be used to create a table of perfect moves.
These perfect moves are precalculated at startup and stored in a 12288 byte table with an
"open-address" hash scheme.
</p>

<p>
I think that the time and space complexity of the engine can be improved with minimal
perfect hashing. However, I was unable to find an easy method (not enough time on my 
hands, unfortunately). If you can find a method, please let me know and I'll add you 
to the project!
</p>

## *Average Best Move Calculation Time*

1 microsecond.

## *Table vs. Alpha-Beta (In seconds, from home position)*

![chart](/figures/tictac.png)

