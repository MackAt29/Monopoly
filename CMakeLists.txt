cmake_minimum_required(VERSION 3.2)

project(Monopoly)

add_library(Board
Board.h
Board.cpp
)

add_library(Player
Player.h
Player.cpp
)

add_library(Property
Property.h
Property.cpp
)

add_executable(main
main.cpp
)

target_link_libraries(
Board
Player
Property
)
