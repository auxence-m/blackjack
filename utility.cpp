//
// Created by AuxenceM on 2025-05-21.
//
#include "utility.h"
#include <limits>

std::string askYesOrNoQuestion(const std::string &question) {
    std::string res;
    std::cout << question;
    std::cin >> res;

    while (res != "Y" && res != "N" ) {
        std::cout << "Please answer (Y) for Yes or (N) for No." << std::endl;
        std::cout << question;
        std::cin.clear();
        std::cin >> res;
    }
    return res;
}

std::string askHitOrStandQuestion(const std::string& question) {
    std::string res;
    std::cout << question;
    std::cin >> res;

    while (res != "H" && res != "S" ) {
        std::cout << "Please answer (H) for Hit or (S) for Stand." << std::endl;
        std::cout << question;
        std::cin.clear();
        std::cin >> res;
    }
    return res;
}


int askBetQuestion(const int cash) {
    // Ask player to place a bet
    int bet = 0;
    std::cout << "You have " << cash << "$" << std::endl;
    std::cout << "How much would you like to bet?:";
    std::cin >> bet;

    // Check for invalid input first
    while (std::cin.fail()) {
        std::cout << "Invalid input!! Please enter an integer value" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "How much would you like to bet?:";
        std::cin >> bet;
    }

    while (bet == 0 || bet > cash) {
        std::cout << "You cannot bet more than " << cash << "$" << std::endl;
        std::cout << "How much would you like to bet?:";
        std::cin >> bet;
    }
    return bet;
}

