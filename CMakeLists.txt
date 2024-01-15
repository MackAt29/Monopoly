cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(monopoly_cpp)

include_directories(include)

add_library(BoardLib
include/Board.h
src/Board.cpp
)

add_library(PlayerLib
include/Player.h
src/Player.cpp
)

add_library(PropertyLib
include/Property.h
src/Property.cpp
)

add_executable(main
src/main.cpp
)

target_link_libraries(main
BoardLib
PlayerLib
PropertyLib
)

