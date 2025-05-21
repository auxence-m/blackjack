#include <iostream>
#include <cstdio>
#include <windows.h>
#include "cardFactory.h"
#include "player.h"
#include "deck.h"
#include "utility.h"


int main() {
    SetConsoleOutputCP(CP_UTF8);
    const auto game = "BlackJack";
    std::cout << "Hello and welcome to " << game << "!\n";

    // Create players
    Dealer dealer;
    Player player;

    std::string answer = askYesOrNoQuestion("Would you like to play ? (Y)/(N): ");

    while (answer == "Y") {
        // Create card factory and get deck of 52 cards
        CardFactory* factory = CardFactory::getFactory();
        Deck deck = factory->getDeck();

        // Clear dealer and player hands and their total points
        dealer.clear();
        player.clear();

        bool winOrLose = false;

        //Check if player still has some cash
        if (player.getCash() == 0) {
            std::cout << "You have " << player.getCash() << "$" << std::endl;
            std::cout << "Sorry you have no more money ☹️." << std::endl;
            std::cout << "You can start a new game if you would like to start over." << std::endl;
            std::cout << "Thank you for playing" << std::endl;
            exit(EXIT_SUCCESS);
        }

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
        // Dealer hand first stays face down until players decides to stand
        // Dealer total is also the value of the face up card only for now
        std::cout << "You:    ";
        player.printHand();
        std::cout << "(Total " << player.computeTotal() << ")" << std::endl;

        std::cout << "Dealer: ";
        dealer.hideHand();
        std::cout << "(Total " << dealer.hideTotal() << ")" << std::endl;
        std::cout << std::endl;

        // Check for BlackJack
        // Neither de dealer nor the player can lose on the first draw. But they can Blackjack.
        if (player.getTotal() == 21) {
            std::cout << "😀 BLACKJACK, YOU WIN!!!" << std::endl;
            player.setCash(player.getCash() + bet);
            winOrLose = true;
        }

        // Hit or Stand
        if (!winOrLose) {
            answer = askHitOrStandQuestion("Hit or Stand ? (H)/(S): ");
        }

        while (answer == "H" and !winOrLose) {
            player.addCard(deck.drawCard());

            std::cout << "You:    ";
            player.printHand();
            std::cout << "(Total " << player.computeTotal() << ")" << std::endl;

            std::cout << "Dealer: ";
            dealer.hideHand();
            std::cout << "(Total " << dealer.hideTotal() << ")" << std::endl;
            std::cout << std::endl;

            // Check for BlackJack or loss
            if (player.getTotal() == 21) {
                std::cout << "😀 BLACKJACK, YOU WIN!!!" << std::endl;
                player.setCash(player.getCash() + bet);
                winOrLose = true;
                break;
            }
            if (player.getTotal() > 21) {
                std::cout << "☹️ YOU LOSE!!!" << std::endl;
                player.setCash(player.getCash() - bet);
                winOrLose = true;
                break;
            }

            answer = askHitOrStandQuestion("Hit or Stand ? (H)/(S): ");
        }

        if (answer == "S") {
            // Dealer plays
            // Dealer reveals hidden card.
            std::cout << "You:    ";
            player.printHand();
            std::cout << "(Total " << player.computeTotal() << ")" << std::endl;

            std::cout << "Dealer: ";
            dealer.printHand();
            std::cout << "(Total " << dealer.computeTotal() << ")" << std::endl;
            std::cout << std::endl;

            // check for win or loss
            if (dealer.getTotal() > player.getTotal()) {
                std::cout << "☹️ YOU LOSE!!!"<< std::endl;
                player.setCash(player.getCash() - bet);
                winOrLose = true;
            } else if (dealer.getTotal() < player.getTotal()) {
                if (dealer.getTotal() >= 17) {
                    std::cout << "☺️ YOU WIN!!!" << std::endl;
                    player.setCash(player.getCash() + bet);
                    winOrLose = true;
                }
            } else if (dealer.getTotal() == player.getTotal()) {
                std::cout << "😁 IT'S A DRAW!!" << std::endl;
                winOrLose = true;
            }

            // Dealer must hit if its total is 16 or lower and stand if its total is 17 or higher
            while (dealer.getTotal() < 17 && !winOrLose ) {
                dealer.addCard(deck.drawCard());

                std::cout << "You:    ";
                player.printHand();
                std::cout << "(Total " << player.computeTotal() << ")" << std::endl;

                std::cout << "Dealer: ";
                dealer.printHand();
                std::cout << "(Total " << dealer.computeTotal() << ")" << std::endl;
                std::cout << std::endl;

                // check for win or loss
                if (dealer.getTotal() > player.getTotal()) {
                    std::cout << "☹️ YOU LOSE!!!" << std::endl;
                    player.setCash(player.getCash() - bet);
                    winOrLose = true;
                } else if (dealer.getTotal() < player.getTotal()) {
                    if (dealer.getTotal() >= 17) {
                        std::cout << "☺️ YOU WIN!!!" << std::endl;
                        player.setCash(player.getCash() + bet);
                        winOrLose = true;
                    }
                } else if (dealer.getTotal() == player.getTotal()) {
                    std::cout << "😁 IT'S A DRAW!!" << std::endl;
                    winOrLose = true;
                }
            }
        }

        if (winOrLose) {
            answer = askYesOrNoQuestion("Would you like to play again ? (Y)/(N): ");
        }
    }

    // Answer is No
    std::cout << "Thank You for playing." << std::endl;
    return 0;
}