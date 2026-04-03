#include "UI.h"
#include <iostream>
#include <algorithm>
#include <cctype>

std::string UI::getPlayerChoice() const {
    std::string choice;
    std::getline(std::cin, choice);

    // Normalize once here so the rest of the game can stay focused on logic.
    choice.erase(choice.begin(), std::find_if(choice.begin(), choice.end(),
        [](unsigned char ch) { return !std::isspace(ch); }));
    choice.erase(std::find_if(choice.rbegin(), choice.rend(),
        [](unsigned char ch) { return !std::isspace(ch); }).base(), choice.end());

    std::transform(choice.begin(), choice.end(), choice.begin(),
        [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

    return choice;
}
