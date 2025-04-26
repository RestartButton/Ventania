#pragma once
#include <string>
#include "GameState.hpp"

class PlayingState;

class SavingState : public GameState {
    bool exitRequested = false;
    PlayingState& jogo;
private:
    void salvarJogo(const PlayingState& state, const std::string& nomeArquivo);
public:
    SavingState(PlayingState& joj);
    void handleInput(char input);
    void update();
    void render();
    bool shouldPop();
};