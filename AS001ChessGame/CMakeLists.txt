cmake_minimum_required(VERSION 3.24)
project(AS001ChessGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(AS001ChessGame chess.h chess_main.cpp chess.cpp)
