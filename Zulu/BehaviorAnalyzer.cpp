#include "BehaviorAnalyzer.h"

BehaviorAnalyzer::BehaviorAnalyzer() {
}

void BehaviorAnalyzer::logAction(const std::string& action) {
    history.push_back(action);
}

bool BehaviorAnalyzer::isRepetitive(const std::string& action) const {
    if (history.size() < 3)
        return false;

    int count = 0;
    for (int i = history.size() - 3; i < history.size(); i++) {
        if (history[i] == action)
            count++;
    }

    return count == 3;
}