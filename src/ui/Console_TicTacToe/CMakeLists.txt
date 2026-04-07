cmake_minimum_required(VERSION 3.0)
project(Console_TicTacToe)
include_directories(../../engine/)
SET(SOURCE_FILE ./Console_TicTacToe.cpp
../../engine/TicTacToeBoard.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILE})
