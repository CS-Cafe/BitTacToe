//
// Created by evcmo on 10/26/2021.
//

#pragma once
#ifndef BITTACTOE_BOARD_H
#define BITTACTOE_BOARD_H
#include <ostream>
#include <iostream>
#include <cassert>

namespace bit {

    constexpr uint8_t BoardLength = 9;

    /**
     * Bitboards representing the
     * individual squares of the
     * tic-tac-toe board.
     */
    constexpr uint16_t Squares[] = {
            0x0100, 0x0080, 0x0040,
            0x0020, 0x0010, 0x0008,
            0x0004, 0x0002, 0x0001
    };

    /**
     * Magic bitmaps that contain
     * special endgame information
     * for quick access. 512 bits.
     * (64 bytes.)
     */
    constexpr uint8_t Magic[] = {
            128, 128, 128, 128,
            128, 128, 128, 255,
            128, 170, 240, 250,
            128, 170, 240, 255,
            128, 128, 204, 204,
            128, 128, 204, 255,
            128, 170, 252, 254,
            128, 170, 252, 255,
            128, 128, 170, 170,
            240, 240, 250, 255,
            128, 170, 250, 250,
            240, 250, 250, 255,
            128, 128, 238, 238,
            240, 240, 254, 255,
            255, 255, 255, 255,
            255, 255, 255, 255
    };

    /**
     * The DeBruijn constant.
     */
    constexpr uint64_t
    DeBruijn64 = 0x03F79D71B4CB0A89L;

    /**
     * The DeBruijn map from hash key to integer
     * square index.
     */
    constexpr uint8_t DeBruijnTable[] = {
            0,   1, 48,  2, 57, 49, 28,  3,
            61, 58, 50, 42, 38, 29, 17,  4,
            62, 55, 59, 36, 53, 51, 43, 22,
            45, 39, 33, 30, 24, 18, 12,  5,
            63, 47, 56, 27, 60, 41, 37, 16,
            54, 35, 52, 21, 44, 32, 23, 11,
            46, 26, 40, 15, 34, 20, 31, 10,
            25, 14, 19,  9, 13,  8,  7,  6
    };

    /**
     * A method to "scan" the given unsigned long
     * from least significant bit to most significant
     * bit, reporting the index of the fist encountered
     * high bit.
     *
     * @author Martin Läuter (1997),
     * @author Charles E. Leiserson,
     * @author Harald Prokop,
     * @author Keith H. Randall
     * @param l the long to scan
     * @return the integer index of the first high bit
     * starting from the least significant side.
     */
    constexpr int bitScanFwd(const uint64_t l) {
        assert(l != 0);
        return DeBruijnTable[(int)
            (((l & (uint64_t)-(int64_t)l)
            * DeBruijn64) >> 58U)
        ];
    }

    /**
     * A mapping from Alliance to character
     * representation.
     */
    [[maybe_unused]]
    constexpr char AllianceToChar[] = { 'X', 'O' };

    /**
     * The Alliances, enumerated.
     */
    enum Alliance : uint8_t { X, O };

    /**
     * Complement overload.
     * @param a the Alliance to take the complement of
     * @return the complement of the given Alliance
     */
    constexpr Alliance operator~(const Alliance a)
    { return Alliance(a ^ X ^ O); }

    /**
     * @class <b><i>Board</i></b>
     *
     * <p>
     * A tic-tac-toe board.
     *
     * @authors Ellie Moore
     * @authors ...YourNameHere...
     * @version 10.26.2021
     */
    class Board final {
    private:

        /**
         * The bitboard belonging to X.
         */
        uint16_t bbx;

        /**
         * The bitboard belonging to O.
         */
        uint16_t bbo;
    public:

        /**
         * A public constructor for a Board.
         */
        constexpr Board() : bbx(0), bbo(0)
        { }

#       define TERN(A, Q, R) A == X? Q: R
#       define GET_BOARD(A) TERN(A, bbx, bbo)

        /**
         * A function to get the bitboard layer
         * of the given alliance.
         *
         * @tparam A the alliance
         * @return the bitboard layer of the
         * given alliance
         */
        template<Alliance A>
        constexpr uint16_t get()
        { return GET_BOARD(A); }

#       define PLACE_MARK(A, I) \
        TERN(A, bbx ^= Squares[I], bbo ^= Squares[I])
#       define AssertTA \
        static_assert(A == X || A == O)
#       define AssertTI \
        static_assert(I >= 0 && I < BoardLength)
#       define AssertA \
        assert(a == X || a == O)
#       define AssertI \
        assert(i >= 0 && i < BoardLength)

        /**
         * A function to make or unmake a mark
         * on the board.
         *
         * @tparam A the Alliance to mark with
         * @tparam I the square to mark
         */
        template<Alliance A, int I>
        [[maybe_unused]]
        constexpr void mark()
        { AssertTA; AssertTI; PLACE_MARK(A, I); }

        /**
        * A function to make or unmake a mark
        * on the board.
        *
        * @tparam A the Alliance to mark with
        * @param i the square to mark
        */
        template<Alliance A>
        constexpr void mark(const int i)
        { AssertTA; AssertI; PLACE_MARK(A, i); }

        /**
        * A function to make or unmake a mark
        * on the board.
        *
        * @param a the Alliance to mark with
        * @param i the square to mark
        */
        [[maybe_unused]] constexpr void
        mark(const Alliance a, const int i)
        { AssertA; AssertI; PLACE_MARK(a, i); }

#       undef PLACE_MARK
#       define SQUARE_FULL(i) (bbx | bbo) & Squares[i]

        /**
         * A method to check if the square at a given
         * index is empty.
         *
         * @param i the index
         * @return whether the square at a given index
         * is empty
         */
        [[maybe_unused]] [[nodiscard]]
        constexpr bool
        emptySquare(const int i) const
        { AssertI; return !(SQUARE_FULL(i)); }

        /**
         * A method to check if the square at a given
         * index is occupied.
         *
         * @param i the index
         * @return whether the square at a given index
         * is occupied
         */
        [[nodiscard]]
        constexpr bool
        occupiedSquare(const int i) const
        { AssertI; return SQUARE_FULL(i); }

#       undef SQUARE_FULL
#       undef AssertTI
#       undef AssertI
#       define EXTRACT_MAGIC(A)                        \
        do {                                           \
            const uint16_t t = GET_BOARD(A); \
            return Magic[t >> 3U] & (1U << (t & 7U));  \
        } while(0)

        /**
         * A function to determine whether or not
         * a given alliance is victorious. That is,
         * whether the alliance has three in a row.
         *
         * @tparam A the Alliance
         * @return whether the alliance has three in a row
         */
        template<Alliance A>
        constexpr bool hasVictory()
        { AssertTA; EXTRACT_MAGIC(A); }

        /**
         * A function to determine whether or not
         * a given alliance is victorious. That is,
         * whether the alliance has three in a row.
         *
         * @param a the Alliance
         * @return whether the alliance has three in a row
         */
        [[maybe_unused]] constexpr bool
        hasVictory(const Alliance a)
        { AssertA; EXTRACT_MAGIC(a); }

#       undef EXTRACT_MAGIC
#       undef TERN
#       undef GET_BOARD
#       undef AssertTA
#       undef AssertA

        /**
         * A method to indicate whether this board is full.
         *
         * @return whether this board is full.
         */
        [[nodiscard]]
        constexpr bool isFull() const
        { return (bbx | bbo) == 0x01FF; }


        /**
         * A method to reset this board to its empty
         * state.
         */
        constexpr void reset()
        { bbx = bbo = 0; }

        /**
         * Insertion overload.
         */
        friend std::ostream&
        operator<<(std::ostream& out, const Board& b) {
            uint16_t p = b.bbx;
            uint16_t q = b.bbo;
            char u[BoardLength];
            for(char
                * d = u,
                * c = u + BoardLength;
                    d < c;) *d++ = '-';
            for(; p; p &= p - 1)
                u[bitScanFwd(p)] = 'x';
            for(; q; q &= q - 1)
                u[bitScanFwd(q)] = 'o';
            out << "\n "
                << u[0] << " | " << u[1] << " | " << u[2]
                << "\n---+---+---\n "
                << u[3] << " | " << u[4] << " | " << u[5]
                << "\n---+---+---\n "
                << u[6] << " | " << u[7] << " | " << u[8]
                << '\n';
            return out;
        }
    }; // class Board
} // namespace bit

#endif //BITTACTOE_BOARD_H
