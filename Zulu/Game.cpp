#include "Game.h"
#include <iostream>
#include <memory>                
#include "ResourceDecayRule.h"
#include "ExploreScene.h"
#include "FortifyScene.h"
#include "ExpandScene.h"

GameState& Game::getState() {
    return state;
}

Game::Game() : isRunning(true), mutationTriggered(false) {
    // Start simple so scene changes and rule changes are easy to notice.
    state.resources = 10;
    state.stability = 10;
    state.influence = 5;
    state.turn = 1;
}

void Game::printHUD() const {
    std::cout << "\n==================================================\n";
    std::cout << "[ COMMAND INTERFACE :: SECTOR-7 ]\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << " TURN: " << state.turn
        << " | RESOURCES: " << state.resources
        << " | STABILITY: " << state.stability
        << " | INFLUENCE: " << state.influence << "\n";
    std::cout << "==================================================\n\n";
}

void Game::run() {
    while (isRunning) {
        processTurn();

        if (checkGameOver()) {
            isRunning = false;
        }

        nextTurn();
    }

    std::cout << "\nGame Over.\n";
}

void Game::processTurn() {
    printHUD();

    std::cout << "Choose an action:\n";
    std::cout << " 1) Explore\n";
    std::cout << " 2) Fortify\n";
    std::cout << " 3) Expand\n";
    std::cout << "\n> ";

    std::string choice = ui.getPlayerChoice();

    // Keep the top-level loop small.
    // Scenes own the actual moment-to-moment interaction.
    handlePlayerChoice(choice);

    behaviorAnalyzer.logAction(choice);

    checkForMutations(choice);

    ruleEngine.applyRules(state);
}

void Game::handlePlayerChoice(const std::string& choice) {
    if (choice == "1" || choice == "explore") {
        currentScene = std::make_unique<ExploreScene>();
    }
    else if (choice == "2" || choice == "fortify") {
        currentScene = std::make_unique<FortifyScene>();
    }
    else if (choice == "3" || choice == "expand") {
        currentScene = std::make_unique<ExpandScene>();
    }
    else {
        std::cout << "Invalid choice.\n";
        return;
    }

    // Swap in the selected scene and let it drive until it hands control back.
    currentScene->run(*this);
}

void Game::checkForMutations(const std::string& choice) {
    if (!mutationTriggered && behaviorAnalyzer.isRepetitive(choice)) {
        std::cout << "\n A new force has emerged...\n";

        ruleEngine.addRule(new ResourceDecayRule());
        mutationTriggered = true;
    }
}

bool Game::checkGameOver() const {
    if (state.resources <= 0 || state.stability <= 0) {
        return true;
    }

    return false;
}

void Game::modifyResources(int amount) {
    state.resources += amount;
}

void Game::modifyStability(int amount) {
    state.stability += amount;
}

void Game::modifyInfluence(int amount) {
    state.influence += amount;
}

int Game::getResources() const {
    return state.resources;
}

int Game::getStability() const {
    return state.stability;
}

int Game::getInfluence() const {
    return state.influence;
}

void Game::nextTurn() {
    state.turn++;
}
