#include "Game.h"
#include <iostream>
#include <memory>                
#include "ResourceDecayRule.h"
#include "ExploreScene.h"
#include "FortifyScene.h"
#include "ExpandScene.h"


// STATE ACCESS

/*
    Returns reference to internal GameState.

    This allows Scene objects to access and modify
    the world stats through the Game interface.
*/
GameState& Game::getState() {
    return state;
}


//CONSTRUCTOR
/*
    Constructor initializes:
    - Control flags
    - Starting world stats
*/
Game::Game() : isRunning(true), mutationTriggered(false) {

    // Initial world balance
    state.resources = 10;
    state.stability = 10;
    state.influence = 5;
    state.turn = 1;
}
//you good?
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



// MAIN LOOP

/*
    Runs until game over condition is reached.
*/
void Game::run() {

    // FIX:
    // Removed initial HUD + menu printing from here
    // to prevent duplicate interface display.

    while (isRunning) {

        processTurn();  // Execute one full turn cycle

        // Check losing conditions
        if (checkGameOver()) {
            isRunning = false;
        }

        nextTurn();     // Advance turn counter safely
    }

    std::cout << "\nGame Over.\n";
}


// TURN PIPELINE

/*
    Order of execution per turn:

    1. Display world state
    2. Get player input
    3. Execute Scene logic
    4. Log player behavior
    5. Inject mutations if needed
    6. Apply global rules
*/
void Game::processTurn() {

    printHUD();

    // FIX:
    // Menu printing moved here so it displays once per turn.
    std::cout << "Choose an action:\n";
    std::cout << " 1) Explore\n";
    std::cout << " 2) Fortify\n";
    std::cout << " 3) Expand\n";
    std::cout << "\n> ";

    std::string choice = ui.getPlayerChoice();

    handlePlayerChoice(choice);

    behaviorAnalyzer.logAction(choice);

    checkForMutations(choice);

    ruleEngine.applyRules(state);
}


//SCENE DISPATCH

/*
    Creates the appropriate Scene dynamically.

    We use std::unique_ptr so memory is automatically
    cleaned up when scene changes.
*/
void Game::handlePlayerChoice(const std::string& choice) {

    if (choice == "1") {
        currentScene = std::make_unique<ExploreScene>();
    }
    else if (choice == "2") {
        currentScene = std::make_unique<FortifyScene>();
    }
    else if (choice == "3") {
        currentScene = std::make_unique<ExpandScene>();
    }
    else {
        std::cout << "Invalid choice.\n";
        return;
    }

    /*
        Execute the selected scene.

        We pass *this so the scene can interact
        with the Game via public functions.
    */
    currentScene->run(*this);
}


// MUTATION SYSTEM

/*
    If player repeats same action 3 times,
    inject ResourceDecayRule dynamically.
*/
void Game::checkForMutations(const std::string& choice) {

    if (!mutationTriggered && behaviorAnalyzer.isRepetitive(choice)) {

        std::cout << "\n A new force has emerged...\n";

        // Add new adaptive rule
        ruleEngine.addRule(new ResourceDecayRule());

        mutationTriggered = true;
    }
}


//    GAME OVER CHECK

/*
    Game ends if:
    - Resources depleted
    - Stability collapses
*/
bool Game::checkGameOver() const {

    if (state.resources <= 0 || state.stability <= 0) {
        return true;
    }

    return false;
}

/*

                SAFE MODIFIER FUNCTIONS

    These allow Scenes to modify stats
    WITHOUT directly touching GameState.
*/

/*
    Increase or decrease resources.
*/
void Game::modifyResources(int amount) {
    state.resources += amount;
}

/*
    Increase or decrease stability.
*/
void Game::modifyStability(int amount) {
    state.stability += amount;
}

/*
    Increase or decrease influence.
*/
void Game::modifyInfluence(int amount) {
    state.influence += amount;
}

/*
    Getter functions for read only access.
*/
int Game::getResources() const {
    return state.resources;
}

int Game::getStability() const {
    return state.stability;
}

int Game::getInfluence() const {
    return state.influence;
}

/*
    Safely advances the turn counter.
*/
void Game::nextTurn() {
    state.turn++;
}