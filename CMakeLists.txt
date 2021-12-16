cmake_minimum_required(VERSION 3.20)
project(BitTacToe)

set(CMAKE_CXX_STANDARD 23)

add_executable(BitTacToe src/main.cpp src/Board.h src/Opponent.h src/PerfectPlay.h)
