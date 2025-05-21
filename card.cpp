//
// Created by AuxenceM on 2025-05-21.
//

#include "card.h"

Rank Card::getRank() const {
    return rank;
}

std::string Hearts::getFace() const {
    return {"[♥]"};
}

std::string Clubs::getFace() const {
    return {"[♣]"};
}

std::string Diamonds::getFace() const {
    return {"[♦]"};
}

std::string Spades::getFace() const {
    return {"[♠]"};
}



std::ostream &operator<<(std::ostream &os, const Card* card) {
    if (card -> getRank() > ACE && card -> getRank() < JACK) {
        os << card->getRank() << card->getFace();
    }  else if (card -> getRank() == JACK) {
        os << "J" << card->getFace();
    } else if (card -> getRank() == QUEEN) {
        os << "Q" << card->getFace();
    } else if (card -> getRank() == KING) {
        os << "K" << card->getFace();
    } else  {
        os << "A" << card->getFace();
    }
    return os;
}