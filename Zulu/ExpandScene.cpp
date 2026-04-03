#include "ActionKnowledge.h"
#include <iostream>
#include "ExpandScene.h"
#include "Game.h"

void ExpandScene::run(Game& game) {
    std::cout << "\nExpand is still under construction, but it can already share the same freeform input layer.\n";
    std::cout << "That means exploration, expansion, and defense can all react to broad player intent the same way.\n";

    std::string input;
    std::cout << "\nTry an expansion-style action to preview the shared parser:\n> ";
    std::getline(std::cin, input);

    ActionIntent intent = ActionKnowledge::detectIntent(ActionKnowledge::normalize(input));

    if (intent == ActionIntent::Inspect) {
        std::cout << "You scout outward, looking for routes, opportunities, and hidden costs.\n";
    }
    else if (intent == ActionIntent::Vocalize) {
        std::cout << "You project confidence into the unknown. Sometimes expansion starts with declaring intent before you feel ready.\n";
    }
    else if (intent == ActionIntent::Help) {
        std::cout << "Expand will eventually care about scouting, claiming territory, probing risk, and pushing beyond the safe perimeter.\n";
    }
    else {
        std::cout << "The parser has a read on the action category already. The scene just needs its specific consequences next.\n";
    }
}
