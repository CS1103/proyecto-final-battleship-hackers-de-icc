cmake_minimum_required(VERSION 3.15)
project(POO_II_BattleShip)

set(CMAKE_CXX_STANDARD 17)

set( CMAKE_VERBOSE_MAKEFILE on)
if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
elseif(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS -pthread)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic -Wextra")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic -Wextra")
endif()

add_executable(POO_II_BattleShip main.cpp BattleShip/server.cpp BattleShip/player.cpp)
if(UNIX AND NOT APPLE)
    target_link_libraries(POO_II_BattleShip stdc++fs)
endif()

