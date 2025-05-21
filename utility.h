//
// Created by AuxenceM on 2025-05-21.
//

#ifndef UTILITY_H
#define UTILITY_H
#include <iostream>
#include <string>

inline std::string askYesOrNoQuestion(const std::string& question) {
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

inline std::string askHitOrStandQuestion(const std::string& question) {
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
#endif //UTILITY_H
