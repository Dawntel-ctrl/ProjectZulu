#include "ResourceDecayRule.h"

void ResourceDecayRule::apply(GameState& state) {
    state.resources -= 1;  // Lose 1 resource every turn
}

std::string ResourceDecayRule::getName() const {
    return "Resource Decay";
}