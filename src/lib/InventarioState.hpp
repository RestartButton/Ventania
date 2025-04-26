#pragma once
#include "GameState.hpp"
#include "Inventario.hpp"

class InventarioState : public GameState {
    bool exitRequested = false;
    Inventario& bag;
public:
    InventarioState(Inventario& inv);
    void handleInput(char input) override;
    void update() override;
    void render() override;
    bool shouldPop();
};