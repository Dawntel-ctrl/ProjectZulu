#pragma once

#include <initializer_list>
#include <string>

enum class ActionIntent {
    Help,
    Inspect,
    Console,
    Listen,
    Machine,
    Door,
    BodyFunction,
    Vocalize,
    Aggressive,
    Wait,
    Unknown
};

namespace ActionKnowledge {
// This stays intentionally fuzzy so scenes can react to intent
// without caring about the exact sentence the player typed.
std::string normalize(std::string text);
bool containsAny(const std::string& input, std::initializer_list<std::string> keywords);
ActionIntent detectIntent(const std::string& input);
}
