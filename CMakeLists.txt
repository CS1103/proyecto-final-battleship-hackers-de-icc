cmake_minimum_required(VERSION 3.15)
project(POO_II_BattleShip)

set(CMAKE_CXX_STANDARD 17)

add_executable(POO_II_BattleShip main.cpp BattleShip/player.cpp BattleShip/Controller.cpp)
