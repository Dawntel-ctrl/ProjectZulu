#pragma once
#include <string>
#include "GameState.h"

class Rule {
public:
    virtual void apply(GameState& state) = 0;
    virtual std::string getName() const = 0;
    virtual ~Rule() {}
};