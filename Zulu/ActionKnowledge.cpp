#include "ActionKnowledge.h"

#include <algorithm>
#include <cctype>

namespace ActionKnowledge {
std::string normalize(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(),
        [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
    return text;
}

bool containsAny(const std::string& input, std::initializer_list<std::string> keywords) {
    for (const std::string& keyword : keywords) {
        if (input.find(keyword) != std::string::npos) {
            return true;
        }
    }

    return false;
}

ActionIntent detectIntent(const std::string& input) {
    // Order matters here. Specific objects should win before broad verbs.
    if (containsAny(input, { "help", "hint", "what can i do", "options" })) {
        return ActionIntent::Help;
    }

    if (containsAny(input, { "console", "terminal", "panel", "screen", "broken console" })) {
        return ActionIntent::Console;
    }

    if (containsAny(input, { "listen", "hear", "hum", "sound", "vents" })) {
        return ActionIntent::Listen;
    }

    if (containsAny(input, { "approach", "touch", "use machine", "machine", "device", "keypad" })) {
        return ActionIntent::Machine;
    }

    if (containsAny(input, { "door", "leave", "exit", "open door" })) {
        return ActionIntent::Door;
    }

    if (containsAny(input, { "shit", "poop", "crap", "take a dump", "take a shit", "piss", "pee", "urinate" })) {
        return ActionIntent::BodyFunction;
    }

    if (containsAny(input, { "yell", "shout", "scream", "call out", "sing" })) {
        return ActionIntent::Vocalize;
    }

    if (containsAny(input, { "hit", "kick", "punch", "attack", "smash", "break" })) {
        return ActionIntent::Aggressive;
    }

    if (containsAny(input, { "wait", "sit", "rest", "think", "breathe", "meditate" })) {
        return ActionIntent::Wait;
    }

    // Inspect is intentionally late because words like "look at console"
    // should land on the console branch instead of the generic room branch.
    if (containsAny(input, { "inspect", "search", "look", "room", "surround", "wall", "floor" })) {
        return ActionIntent::Inspect;
    }

    return ActionIntent::Unknown;
}
}
