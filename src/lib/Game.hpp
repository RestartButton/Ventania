#pragma once
#include <memory>
#include <stack>
#include "GameState.hpp"


class Game {
    std::stack<std::unique_ptr<GameState>> states;
    bool running = true;
public:
    void pushState(std::unique_ptr<GameState> state);
    void replaceState(std::unique_ptr<GameState> state);
    void popState();
    void gameLoop();
};