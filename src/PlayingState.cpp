#include "Game.hpp"
#include "PlayingState.hpp"
#include "SavingState.hpp"

void PlayingState::handleInput(char input) {
    if (input == 'b') {
        std::cout << "-> Voltando para o Menu...\n";
        exitRequested = true;
    } else if (input == 'i') {
        std::cout << "-> Abrindo a Mochila...\n";
        game->pushState(std::make_unique<InventarioState>(bag));
    } else if (input == 's') {
        std::cout << "-> Iniciando Salvamento...\n";
        game->pushState(std::make_unique<SavingState>(*this));
    }
}

void PlayingState::update() {}

void PlayingState::render() {
    std::cout << "=== JOGANDO ===\n";
    std::cout << "i. Abrir Inventario\n";
    std::cout << "s. Salvar Jogo\n";
    std::cout << "b. Voltar ao Menu\n";
}

void PlayingState::save(std::ostream& out) const {
    bag.save(out);
}

void PlayingState::load(std::istream& in) {
    bag.load(in);
}

bool PlayingState::shouldPop() {
    return exitRequested;
}