//
// Created by AuxenceM on 2025-05-21.
//

#include "cardFactory.h"

CardFactory* CardFactory::factory_instance = nullptr;

CardFactory::CardFactory() {
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

CardFactory* CardFactory::getFactory() {
    if (factory_instance == nullptr) {
        factory_instance = new CardFactory();
    }
    return factory_instance;
}

Deck CardFactory::getDeck() {
    // Shuffle deck each time
    const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto engine = std::default_random_engine(seed);
    std::shuffle(deck.begin(), deck.end(), engine);

    return deck;
}
