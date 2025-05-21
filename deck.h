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
    ~Deck() = default;
    std::vector<Card*>::iterator begin();
    std::vector<Card*>::iterator end();
};

#endif //DECK_H
