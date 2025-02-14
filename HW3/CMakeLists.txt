cmake_minimum_required(VERSION 3.28)
project(HW3)

set(CMAKE_CXX_STANDARD 17)

include_directories(dry)
include_directories(wet)

add_executable(HW3
        main.cpp
        Person.cpp
        Person.h
        Task.cpp
        Task.h
        SortedList.h
        TaskManager.cpp
        TaskManager.h

)
