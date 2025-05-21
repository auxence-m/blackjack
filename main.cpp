#include <iostream>
#include <windows.h>
#include "cardFactory.h"
#include "playerBase.h"
#include "deck.h"
#include "utility.h"

//TODO: Document methods
//TODO: Add more comment where necessary

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
        const int bet = askBetQuestion(player.getCash());

        std::cout << "You bet " <<  bet << "$" << std::endl;
        std::cout << "Dealing card...." << std::endl;
        std::cout << std::endl;

        // Deal card 2 to player and dealer
        for (auto i = 0; i < 2; i++) {
            player.addCard(deck.drawCard());
            dealer.addCard(deck.drawCard());
        }

        // Display players hand
        // Dealer hand first card stays face down until players decides to stand
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
            std::cout << "☺️ BLACKJACK, YOU WIN!!!" << std::endl;
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
                std::cout << "☺️ BLACKJACK, YOU WIN!!!" << std::endl;
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

        // Dealer's turn to play
        if (answer == "S") {
            // Dealer reveals hidden card first.
            std::cout << "You:    ";
            player.printHand();
            std::cout << "(Total " << player.computeTotal() << ")" << std::endl;

            std::cout << "Dealer: ";
            dealer.printHand();
            std::cout << "(Total " << dealer.computeTotal() << ")" << std::endl;
            std::cout << std::endl;

            // check for win or loss
            if (dealer.getTotal() > player.getTotal()) {
                // Here the dealer's total could never be more than 21 because he only has two cards
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
                // Dealer has to hit as long as its total is less than 17
                if (dealer.getTotal() >= 17) {
                    std::cout << "☺️ IT'S A DRAW!!" << std::endl;
                    winOrLose = true;
                }
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
                    if (dealer.getTotal() > 21) {
                        std::cout << "☺️ YOU WIN!!!" << std::endl;
                        player.setCash(player.getCash() - bet);
                        winOrLose = true;
                    } else {
                        std::cout << "☹️ YOU LOSE!!!" << std::endl;
                        player.setCash(player.getCash() - bet);
                        winOrLose = true;
                    }
                } else if (dealer.getTotal() < player.getTotal()) {
                    if (dealer.getTotal() >= 17) {
                        std::cout << "☺️ YOU WIN!!!" << std::endl;
                        player.setCash(player.getCash() + bet);
                        winOrLose = true;
                    }
                } else if (dealer.getTotal() == player.getTotal()) {
                    // Dealer has to hit as long as its total is less than 17
                    if (dealer.getTotal() >= 17) {
                        std::cout << "☺️ IT'S A DRAW!!" << std::endl;
                        winOrLose = true;
                    }
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