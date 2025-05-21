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

CardFactory* CardFactory::factory_instance = nullptr;

inline CardFactory::CardFactory() {
    for (int i = 1; i <= 13; i++) {
        deck.addCard(new Hearts(static_cast<Rank>(i)));
    }
    for (int i = 1; i <= 13; i++) {
        deck.addCard(new Clubs(static_cast<Rank>(i)));
    }
    for (int i = 1; i <= 13; i++) {
        deck.addCard(new Diamonds(static_cast<Rank>(i)));
    }
    for (int i = 1; i <= 13; i++) {
        deck.addCard(new Spades(static_cast<Rank>(i)));
    }
}

inline CardFactory* CardFactory::getFactory() {
    if (factory_instance == nullptr) {
        factory_instance = new CardFactory();
    }
    return factory_instance;
}

inline Deck CardFactory::getDeck() {
    // Shuffle deck each time
    const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto engine = std::default_random_engine(seed);
    std::shuffle(deck.begin(), deck.end(), engine);

    return deck;
}



