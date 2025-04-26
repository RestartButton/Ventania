#pragma once
#include <string>
#include <memory>
#include "GameState.hpp"
#include "PlayingState.hpp"


class LoadingState : public GameState {
    bool exitRequested = false;
    bool onMenu = true;
private:
    std::unique_ptr<PlayingState> carregarJogo(const std::string& nomeArquivo);
public:
    void handleInput(char input);
    void update();
    void render();
    bool shouldPop();
};