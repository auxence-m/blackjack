//
// Created by AuxenceM on 2025-05-17.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "card.h"


class Dealer {
    std::vector<Card*> hand = std::vector<Card*>();
    int total = 0;
public:
    int computeTotal();
    void printHand() const;
    void hideHand() const;
    int hideTotal();
    void clear();
    void addCard(Card*);
    int getTotal() const;
    virtual ~Dealer() = default;
};

class Player final : public Dealer {
    int cash = 2500;
public:
    void setCash(int);
    int getCash() const;
};

inline int Dealer::computeTotal() {
    auto aceCount = 0;
    total = 0;
    for (const auto i : hand) {
        if (i -> getRank() == ACE) {
            aceCount++;
            total += 11; // Assumes aces count for 11
        }
        if ( i -> getRank() > ACE && i -> getRank() < JACK) {
            total += i->getRank();
        }
        if (i -> getRank() >= JACK) {
            total += 10;
        }
    }

    if (aceCount > 0 && total > 21) {
        total = total - aceCount * 10;
    }

    return total;
}

inline void Dealer::printHand() const {
    for (const auto i : hand) {
        std::cout << i << " ";
    }
}

inline void Dealer::hideHand() const {
    std::cout << "*[*] " << hand[1] << " ";
}

inline int Dealer::hideTotal() {
    // On the first deal, we only compute the total for the second card in the dealer hand because the first card is hidden
    if (hand.size() == 2) {
        if (hand[1]->getRank() == ACE) {
            total = 11;
        }
        if (hand[1]->getRank() > ACE && hand[1]->getRank() <= TEN) {
            total = hand[1]->getRank();
        }
        if (hand[1]->getRank() > TEN ) {
            total = 10;
        }
    }
    return total;
}

inline void Dealer::addCard(Card* card) {
    hand.push_back(card);
}

inline int Dealer::getTotal() const {
    return total;
}

inline void Dealer::clear() {
    hand.clear();
    total = 0;
}

inline void Player::setCash(const int amount) {
    cash = amount;
}

inline int Player::getCash() const {
    return cash;
}

#endif //PLAYER_H
