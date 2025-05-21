//
// Created by AuxenceM on 2025-05-13.
//

#ifndef CARD_H
#define CARD_H
#include <string>
#include <iostream>

enum Rank {
    ACE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13,
};

class Card {
    Rank rank;
public:
    explicit Card(const Rank r) : rank(r) {}
    virtual ~Card() = default;
    virtual std::string getFace() const = 0;
    virtual Rank getRank() const ;
    friend std::ostream& operator<<(std::ostream& os, const Card* card);
};

class Hearts final : public Card {
public:
    explicit Hearts(const Rank r) : Card(r) {}
    std::string getFace() const override;
};

class Clubs final : public Card {
public:
    explicit Clubs(const Rank r) : Card(r) {}
    std::string getFace() const override;
};

class Diamonds final : public Card {
public:
    explicit Diamonds(const Rank r) : Card(r) {}
    std::string getFace() const override;
};

class Spades final : public Card {
public:
    explicit Spades(const Rank r) : Card(r) {}
    std::string getFace() const override;
};

#endif //CARD_H
