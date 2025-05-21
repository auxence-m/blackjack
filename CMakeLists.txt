cmake_minimum_required(VERSION 3.31)
project(blackjack)

set(CMAKE_CXX_STANDARD 20)

add_executable(blackjack main.cpp
        card.h
        Deck.h
        cardFactory.h
        playerBase.h
        utility.h
        playerBase.cpp
        card.cpp
        cardFactory.cpp
        deck.cpp
        utility.cpp
)
