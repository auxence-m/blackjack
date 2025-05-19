//
// Created by AuxenceM on 2025-05-17.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "card.h"


class Dealer {
protected:
    std::vector<Card*> hand = std::vector<Card*>();
    int total = 0;
public:
    virtual int computeTotal();
    virtual void printHand();
    void addCard(Card*);
    int getTotal() const;
    virtual ~Dealer() = default;
};

class Player final : public Dealer {
    int cash = 2500;
public:
    int computeTotal() override;
    void printHand() override;
    void setCash(int);
    int getCash() const;
};

inline int Dealer::computeTotal() {

    // On the first deal, we only compute the total for the second card in the dealer hand because the first card is hidden
    if (hand.size() == 2) {
        if (hand[1]->getRank() == ACE) {
            return 11;
        }
        if (hand[1]->getRank() > ACE && hand[1]->getRank() <= TEN) {
            return hand[1]->getRank();
        }
        if (hand[1]->getRank() > TEN ) {
            return 10;
        }
    }

    auto aceCount = 0;
    total = 0;
    for (const auto i : hand) {
        if (i -> getRank() == ACE) {
            aceCount++;
            total += 11; // Assumes aces count for 11
        }
        if ( i -> getRank() > TWO && i -> getRank() <= TEN) {
            total += i->getRank();
        }
        if (i -> getRank() > TEN) {
            total += 10;
        }
    }

    if (aceCount > 0 && total > 21) {
        total = total - aceCount * 10;
    }

    return total;
}

inline void Dealer::printHand() {
    // After the first deal, only the second card is shown for the dealer
    if (hand.size() == 2) {
        std::cout << "*[*] " << hand[1] << " ";
    } else {
        for (const auto i : hand) {
            std::cout << i << " ";
        }
    }
}

inline void Dealer::addCard(Card* card) {
    hand.push_back(card);
}

inline int Dealer::getTotal() const {
    return total;
}


inline int Player::computeTotal() {
    auto aceCount = 0;
    total = 0;
    for (const auto i : hand) {
        if (i -> getRank() == ACE) {
            aceCount++;
            total += 11; // Assumes aces count for 11
        }
        if ( i -> getRank() > ACE && i -> getRank() <= TEN) {
            total += i->getRank();
        }
        if (i -> getRank() > TEN) {
            total += 10;
        }
    }

    if (aceCount > 0 && total > 21) {
        total = total - aceCount * 10;
    }

    return total;
}

inline void Player::setCash(const int amount) {
    cash += amount;
}

inline int Player::getCash() const {
    return cash;
}

inline void Player::printHand() {
    for (const auto i : hand) {
        std::cout << i << " ";
    }
}

#endif //PLAYER_H
