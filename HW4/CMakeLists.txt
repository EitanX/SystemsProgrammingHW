cmake_minimum_required(VERSION 3.28)
project(HW4)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(Events)
include_directories(Players)

add_executable(HW4
        Events/Event.h
        Players/Player.h
        main.cpp
        MatamStory.cpp
        MatamStory.h
        Utilities.cpp
        Utilities.h
        Players/Job.h
        Players/Character.h
        Events/Monster.h
        Events/Monster.cpp
        Events/EventFactory.h
        Events/EventFactory.cpp
        Players/PlayerFactory.h
        Players/PlayerFactory.cpp
        Events/Event.cpp
        Players/Character.cpp
        Players/Job.cpp
        Players/Player.cpp
        Players/PlayerStats.h
        Players/PlayerStats.cpp)
