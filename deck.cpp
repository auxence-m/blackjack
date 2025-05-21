//
// Created by AuxenceM on 2025-05-21.
//

#include "deck.h"

Card* Deck::drawCard() {
    if (cards.empty()) {
        return nullptr;
    }

    Card* top = cards.front();
    cards.erase(cards.begin());

    return top;
}

void Deck::addCard(Card* card) {
    cards.push_back(card);
}

std::vector<Card*>::iterator Deck::begin() {
    return cards.begin();
}

std::vector<Card*>::iterator Deck::end() {
    return cards.end();
}
