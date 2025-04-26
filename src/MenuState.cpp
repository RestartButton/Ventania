#include <iostream>
#include <memory>
#include "Game.hpp"
#include "MenuState.hpp"
#include "PlayingState.hpp"
#include "LoadingState.hpp"

void MenuState::handleInput(char input) {
    if (input == 'i') {
        std::cout << "-> Iniciando o Jogo...\n";
        game->pushState(std::make_unique<PlayingState>());
    } else if (input == 'c') {
        std::cout << "-> Iniciando Carregamento...\n";
        game->pushState(std::make_unique<LoadingState>());
    } else if (input == 'q') {
        exitRequested = true;
    }
}

void MenuState::update() {}

void MenuState::render() {
    std::cout << "=== MENU ===\n";
    std::cout << "i. Iniciar Jogo\n";
    std::cout << "c. Carregar Jogo\n";
    std::cout << "q. Sair\n";
}

bool MenuState::shouldPop() {
    return exitRequested;
}
