# Unreasonably Fast Tic Tac Toe
 
A fast tic tac toe project. An excuse to bit-twiddle!  

<p>
The search is now precalculated at startup and stored in a 3*4096 byte table with a 
quadratic open-addressing scheme. I think that this can be improved with perfect hashing. 
However, I was unable to find a multiplier. If you can find a multiplier, please
let me know and I'll add you to the project!
</p>

#### *Average runtime of DFS from home position: 1 microsecond. Lets see if we can go faster (or use less space)!*

# UI

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
