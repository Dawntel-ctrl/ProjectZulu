#pragma once
#include <vector>
#include "Rule.h"
#include "GameState.h"

class RuleEngine {
private:
    std::vector<Rule*> activeRules;

public:
    RuleEngine();
    ~RuleEngine();

    void addRule(Rule* rule);
    void applyRules(GameState& state);
};