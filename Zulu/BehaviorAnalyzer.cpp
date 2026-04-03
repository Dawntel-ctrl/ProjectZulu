#include "BehaviorAnalyzer.h"

BehaviorAnalyzer::BehaviorAnalyzer() : consecutiveCount(0) {}

void BehaviorAnalyzer::logAction(const std::string& action) {
    // We keep both a timeline and a frequency map because they solve
    // different problems once the game starts reacting to play style.
    actionFrequency[action]++;
    history.push_back(action);

    if (action == lastAction) {
        consecutiveCount++;
    }
    else {
        lastAction = action;
        consecutiveCount = 1;
    }
}

bool BehaviorAnalyzer::isRepetitive(const std::string& action) const {
    if (history.size() < 3)
        return false;

    // Looking at the tail keeps this cheap and easy to reason about.
    int count = 0;
    for (size_t i = history.size() - 3; i < history.size(); i++) {
        if (history[i] == action)
            count++;
    }

    return count == 3;
}

int BehaviorAnalyzer::getFrequency(const std::string& action) const {
    auto it = actionFrequency.find(action);

    if (it == actionFrequency.end()) {
        return 0;
    }

    return it->second;
}
