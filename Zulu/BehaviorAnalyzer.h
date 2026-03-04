#pragma once

#include <string>
#include <map>
#include <vector>

// The BehaviorAnalyzer observes player actions.
// It tracks:
// - Full action history
// - Total frequency of each action
// - Consecutive streaks (for mutation triggers)

class BehaviorAnalyzer {
private:
    // Tracks how many times each action has been used overall
    std::map<std::string, int> actionFrequency;

    // Stores every action taken (full timeline)
    std::vector<std::string> history;

    // Used to detect streaks
    std::string lastAction;
    int consecutiveCount;

public:
    // Constructor initializes streak tracking
    BehaviorAnalyzer();

    // Logs a new player action and updates tracking data
    void logAction(const std::string& action);

    // Returns true if the player has repeated the same action 3+ times consecutively
    bool isRepetitive(const std::string& action) const;

    // Returns how many times an action has been used overall
    int getFrequency(const std::string& action) const;
};