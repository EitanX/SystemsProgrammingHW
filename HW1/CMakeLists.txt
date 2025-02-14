cmake_minimum_required(VERSION 3.27)
project(HW1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(mtm_blockchain

        Transaction.h
        Transaction.cpp

        Utilities.h
        Utilities.cpp

        BlockChain.h
        BlockChain.cpp

        main.cpp

)
