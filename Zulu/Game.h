#pragma once

#include <string>
#include "GameState.h"
#include "RuleEngine.h"
#include "BehaviorAnalyzer.h"
#include "UI.h"

class Game {
private:
    GameState state;
    RuleEngine ruleEngine;
    BehaviorAnalyzer behaviorAnalyzer;
    UI ui;

    bool isRunning;
    bool mutationTriggered;

    void processTurn();
    void handlePlayerChoice(const std::string& choice);
    void checkForMutations(const std::string& choice);
    bool checkGameOver() const;

public:
    Game();
    void run();
};