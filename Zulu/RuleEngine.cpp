#include "RuleEngine.h"
#include <iostream>

RuleEngine::RuleEngine() {}

RuleEngine::~RuleEngine() {
    // Still raw pointers for now, so cleanup lives here.
    for (Rule* rule : activeRules) {
        delete rule;
    }
}

void RuleEngine::addRule(Rule* rule) {
    std::cout << "New Rule Activated: " << rule->getName() << "\n";
    activeRules.push_back(rule);
}

void RuleEngine::applyRules(GameState& state) {
    // Rules stack, so every active rule gets a pass each turn.
    for (Rule* rule : activeRules) {
        rule->apply(state);
    }
}
