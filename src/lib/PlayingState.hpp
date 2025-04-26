#pragma once
#include "Serializable.hpp"
#include "GameState.hpp"
#include "InventarioState.hpp"
#include "Map.hpp"
#include "Player.hpp"

class SavingState;

class PlayingState : public GameState, public Serializable {
    bool exitRequested = false;
private:
    Inventario bag;
    Map cur_map;
    Player player;
public:
    PlayingState();

    void handleInput(char input) override;
    void update() override;
    void render() override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
    bool shouldPop() override;
};