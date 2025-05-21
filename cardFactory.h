//
// Created by AuxenceM on 2025-05-13.
//
#pragma once
#include <chrono>
#include <filesystem>
#include <random>

#include "deck.h"

class CardFactory {
    CardFactory();
    Deck deck;
    static CardFactory* factory_instance;
public:
    CardFactory(const CardFactory&) = delete;
    CardFactory& operator=(const CardFactory&) = delete;
    ~CardFactory() = default;
    static CardFactory* getFactory();
    Deck getDeck();


};



