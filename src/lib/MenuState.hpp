#pragma once
#include "GameState.hpp"


class MenuState : public GameState {
    bool exitRequested = false;
public:
    void handleInput(char input) override;
    void update() override;
    void render() override;
    bool shouldPop() override;
};