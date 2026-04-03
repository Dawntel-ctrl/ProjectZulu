#include "ActionKnowledge.h"
#include <iostream>
#include "FortifyScene.h"
#include "Game.h"

void FortifyScene::run(Game& game) {
    std::cout << "\nFortify is still under construction, but the command parser is ready for it.\n";
    std::cout << "When we build this out, actions like `reinforce wall`, `inspect perimeter`, `wait`, or even weird inputs will plug into shared intent handling.\n";

    std::string input;
    std::cout << "\nTry a fortify-style action to preview the shared parser:\n> ";
    std::getline(std::cin, input);

    ActionIntent intent = ActionKnowledge::detectIntent(ActionKnowledge::normalize(input));

    if (intent == ActionIntent::Inspect) {
        std::cout << "You survey your defenses and look for weak points.\n";
    }
    else if (intent == ActionIntent::Aggressive) {
        std::cout << "You throw force at the problem, but fortification usually rewards planning more than violence.\n";
    }
    else if (intent == ActionIntent::Wait) {
        std::cout << "Holding position can be useful, especially if you are listening for pressure points in the environment.\n";
    }
    else if (intent == ActionIntent::Help) {
        std::cout << "Fortify will eventually care about barriers, chokepoints, repairs, and threat anticipation.\n";
    }
    else {
        std::cout << "The shared parser recognizes the tone of that action even though this scene is still a stub.\n";
    }
}
