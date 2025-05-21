//
// Created by AuxenceM on 2025-05-17.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "card.h"


class PlayerBase {
protected:
    std::vector<Card*> hand = std::vector<Card*>();
    int total = 0;
public:
    int computeTotal();
    void printHand() const;
    void clear();
    void addCard(Card*);
    int getTotal() const;
    ~PlayerBase() = default;
};

class Dealer: public PlayerBase {
public:
    void hideHand() const;
    int hideTotal();
};

class Player final : public PlayerBase {
    int cash = 2500;
public:
    void setCash(int);
    int getCash() const;
};

#endif //PLAYER_H
