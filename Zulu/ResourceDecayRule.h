#pragma once
#include "Rule.h"

class ResourceDecayRule : public Rule {
public:
    void apply(GameState& state) override;
    std::string getName() const override;
};
