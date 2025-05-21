//
// Created by AuxenceM on 2025-05-21.
//

#include "playerBase.h"
#include <iostream>

int PlayerBase::computeTotal() {
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

void PlayerBase::printHand() const {
    for (const auto i : hand) {
        std::cout << i << " ";
    }
}

void PlayerBase::clear() {
    hand.clear();
    total = 0;
}

void PlayerBase::addCard(Card* card) {
    hand.push_back(card);
}

int PlayerBase::getTotal() const {
    return total;
}

void Dealer::hideHand() const {
    std::cout << "*[*] " << hand[1] << " ";
}

int Dealer::hideTotal() {
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

void Player::setCash(const int amount) {
    cash = amount;
}

int Player::getCash() const {
    return cash;
}





