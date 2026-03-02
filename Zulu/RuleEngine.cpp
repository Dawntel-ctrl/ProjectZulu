#include "RuleEngine.h"
#include <iostream>

RuleEngine::RuleEngine() {}

RuleEngine::~RuleEngine() {
    for (Rule* rule : activeRules) {
        delete rule;
    }
}

void RuleEngine::addRule(Rule* rule) {
    std::cout << "New Rule Activated: " << rule->getName() << "\n";
    activeRules.push_back(rule);
}

void RuleEngine::applyRules(GameState& state) {
    for (Rule* rule : activeRules) {
        rule->apply(state);
    }
}