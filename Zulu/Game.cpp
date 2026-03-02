#include "Game.h"
#include <iostream>
#include "ResourceDecayRule.h"

Game::Game() : isRunning(true), mutationTriggered(false) {
    state.resources = 10;
    state.stability = 10;
    state.influence = 5;
    state.turn = 1;
}

void Game::run() {
    while (isRunning) {
        processTurn();

        if (checkGameOver()) {
            isRunning = false;
        }

        state.turn++;
    }

    std::cout << "\nGame Over.\n";
}
// This is the heart of the loop
void Game::processTurn() {
    ui.displayState(state);

    std::string choice = ui.getPlayerChoice();

    handlePlayerChoice(choice);

    behaviorAnalyzer.logAction(choice);

    checkForMutations(choice);

    ruleEngine.applyRules(state);
}
// expand me later... Keep base effects simple for now.
void Game::handlePlayerChoice(const std::string& choice) {
    if (choice == "1") {          // Explore
        state.resources += 2;
        state.stability -= 1;
    }
    else if (choice == "2") {     // Fortify
        state.stability += 2;
        state.resources -= 1;
    }
    else if (choice == "3") {     // Expand
        state.influence += 2;
        state.resources -= 2;
    }
}
// This is where the engine starts to feel alive. For now:
//If player repeats same action 3 times ? add a decay rule.

void Game::checkForMutations(const std::string& choice) {
    if (!mutationTriggered && behaviorAnalyzer.isRepetitive(choice)) {
        std::cout << "\n? A new force has emerged...\n";
        ruleEngine.addRule(new ResourceDecayRule());
        mutationTriggered = true;
    }
}
//checkGameOver
bool Game::checkGameOver() const {
    if (state.resources <= 0 || state.stability <= 0) {
        return true;
    }

    return false;
}