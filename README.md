# BitTacToe
 
Minimalist tic tac toe project. An excuse to bit-twiddle!  

### ***A bit of explanation:***
The magic numbers used to check for victory are segments of a 512-bit map. Here, each of the 512 states of a single bitboard are assigned a score of 0 or 1 depending on whether the state is terminal. For speed, this scheme relies heavily on caching, which is almost guaranteed to help during DFS.

### ***Note:***

I randomly came up with this scheme. I'm pretty sure there are ways to optimize further... I just couldn't think of another one that considered both time and memory. Please give the problem a try if you are in the mood for it :)

#### *Average runtime of DFS from home position: 128 microseconds. Lets see if we can go faster!*

# UI

<pre>
 <code>
        - | - | o
       ---+---+---
        - | x | -
       ---+---+---
        - | - | -
       I took 0.000127 seconds!
       Make a move (1-9)
       9 8 7
       6 5 4
       3 2 1
       >>_
 </code>
</pre>
