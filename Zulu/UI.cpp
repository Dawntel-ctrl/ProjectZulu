#include "UI.h"
#include <iostream>

//void UI::displayState(const GameState& state) const {
    //std::cout << "\nTurn: " << state.turn << "\n";
    //std::cout << "Resources: " << state.resources << "\n";
    //std::cout << "Stability: " << state.stability << "\n";
    //std::cout << "Influence: " << state.influence << "\n";

//    std::cout << "\nChoose an action:\n";
  //  std::cout << "1) Explore\n";
    //std::cout << "2) Fortify\n";
   // std::cout << "3) Expand\n";
//}

std::string UI::getPlayerChoice() const {
    std::string choice;
    std::cout << "Enter choice: ";
    std::cin >> choice;
    return choice;
}