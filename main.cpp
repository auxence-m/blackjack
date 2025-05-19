#include <iostream>
#include <cstdio>
#include <windows.h>
#include "cardFactory.h"
#include "player.h"
#include "deck.h"


int main() {
    SetConsoleOutputCP(CP_UTF8);
    const auto game = "BlackJack";
    std::cout << "Hello and welcome to " << game << "!\n";

    std::string answer;
    std::cout << "Would you like to play ? (Y)/(N): ";
    std::cin >> answer;

    while (answer == "Y" || answer == "y") {
        // Create card factory and get deck of 52 cards
        CardFactory* factory = CardFactory::getFactory();
        Deck deck = factory->getDeck();

        // Create players
        Dealer dealer;
        Player player;

        bool winOrLose = false;

        // Ask player to place a bet
        int bet = 0;
        std::cout << "You have " << player.getCash() << "$" << std::endl;
        std::cout << "How much would you like to bet?:";
        std::cin >> bet;

        while (bet == 0 || bet > player.getCash()) {
            std::cout << "You cannot bet more than " << player.getCash() << "$" << std::endl;
            std::cout << "How much would you like to bet?:";
            std::cin >> bet;
        }

        std::cout << "You bet " <<  bet << "$" << std::endl;
        std::cout << "Dealing card...." << std::endl;
        std::cout << std::endl;

        // Deal card 2 to player and dealer
        for (auto i = 0; i < 2; i++) {
            player.addCard(deck.drawCard());
            dealer.addCard(deck.drawCard());
        }

        // Display players hand
        std::cout << "You:    ";
        player.printHand();
        std::cout << "(Total " << player.computeTotal() << ")" << std::endl;

        std::cout << "Dealer: ";
        dealer.printHand();
        std::cout << "(Total " << dealer.computeTotal() << ")" << std::endl;
        std::cout << std::endl;

        // Check for BlackJack
        if (player.getTotal() == 21) {
            std::cout << "BLACKJACK!!! YOU WIN" << std::endl;
            player.setCash(player.getCash() + bet);
            winOrLose = true;
        }
        if (player.getTotal() > 21) {
            std::cout << "YOU LOSE" << std::endl;
            player.setCash(player.getCash() - bet);
            winOrLose = true;
        }

        // Hit or Stand
        std::cout << "Hit or Stand ? (H)/(S): ";
        std::cin >> answer;
        while ((answer == "H" || answer == "h") && !winOrLose) {
            player.addCard(deck.drawCard());

            std::cout << "You:    ";
            player.printHand();
            std::cout << "(Total " << player.computeTotal() << ")" << std::endl;

            std::cout << "Dealer: ";
            dealer.printHand();
            std::cout << "(Total " << dealer.computeTotal() << ")" << std::endl;
            std::cout << std::endl;

            // Check for BlackJack
            if (player.getTotal() == 21) {
                std::cout << "BLACKJACK!!! YOU WIN" << std::endl;
                player.setCash(player.getCash() + bet);
                winOrLose = true;
            }
            if (player.getTotal() > 21) {
                std::cout << "YOU LOSE" << std::endl;
                player.setCash(player.getCash() - bet);
                winOrLose = true;
            }

            std::cout << "Hit or Stand ? (H)/(S): ";
            std::cin >> answer;
        }

        if (answer == "S" || answer == "s") {
            // Dealer plays
            // Reveal dealer hidden card. (Implement function for it)
        }


        if (winOrLose) {
            std::cout << "Would you like to play ? (Y)/(N): ";
            std::cin >> answer;
        }
    }

    // Answer is No
    std::cout << "Thank You!" << std::endl;
    return 0;
}