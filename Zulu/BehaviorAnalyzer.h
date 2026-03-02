#pragma once


#include <string>
#include <map>

class BehaviorAnalyzer {
private:
    std::map<std::string, int> actionFrequency;
    std::string lastAction;
    int consecutiveCount;

public:
    BehaviorAnalyzer();

    void logAction(const std::string& action);

    bool isRepetitive(const std::string& action) const;

    int getFrequency(const std::string& action) const;
};