cmake_minimum_required(VERSION 3.8)

set(This TICTACTOETests)

set(Sources
    TicTacToeTests.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    3D-TICTACTOE
)

add_test(
    NAME ${This}
    COMMAND ${This}
)