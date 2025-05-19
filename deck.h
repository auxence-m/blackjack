//
// Created by AuxenceM on 2025-05-13.
//

#ifndef DECK_H
#define DECK_H
#include <vector>
#include "card.h"

class Deck  {
    std::vector<Card*> cards;
    public:
    Card* drawCard() ;
    void addCard(Card* card);
    size_t getSize() const;
    bool isEmpty() const;
    ~Deck() = default;
    std::vector<Card*>::iterator begin();
    std::vector<Card*>::iterator end();
};

inline Card* Deck::drawCard() {
    if (cards.empty()) {
        return nullptr;
    }

    Card* top = cards.front();
    cards.erase(cards.begin());

    return top;
}

inline void Deck::addCard(Card* card) {
    cards.push_back(card);
}

inline size_t Deck::getSize() const {
    return cards.size();
}

inline bool Deck::isEmpty() const {
    return cards.empty();
}

inline std::vector<Card*>::iterator Deck::begin() {
    return cards.begin();
}

inline std::vector<Card*>::iterator Deck::end() {
    return cards.end();
}

#endif //DECK_H
