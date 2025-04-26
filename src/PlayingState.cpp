#include <cmath>
#include "Game.hpp"
#include "PlayingState.hpp"
#include "SavingState.hpp"

PlayingState::PlayingState()
    : bag(), cur_map(), player(0, 0, 1, 1)
{
    cur_map.loadFromFile("maps/2.map");
    player.map = &cur_map;
}

void PlayingState::handleInput(char input) {
    std::cout << "3";
    if (input == 'b') {
        std::cout << "-> Voltando para o Menu...\n";
        exitRequested = true;
    } else if (input == 'i') {
        std::cout << "-> Abrindo a Mochila...\n";
        game->pushState(std::make_unique<InventarioState>(bag));
    } else if (input == 's') {
        std::cout << "-> Iniciando Salvamento...\n";
        game->pushState(std::make_unique<SavingState>(*this));
    } else {
        player.handleInput(input);
    }
    std::cout << "4";
}

void PlayingState::update() {
    // auto pposition = player.getPos();
    // int x = static_cast<int>(std::round(pposition.first));
    // int y = static_cast<int>(std::round(pposition.second));
    // Tile cur_tile = cur_map.getTile(x, y);
    // if(cur_tile.currentTileID == 3) {
    //     cur_map.loadFromFile("maps/2.map");
    // }
}

void PlayingState::render() {
    std::cout << "=== JOGANDO ===\n";
    cur_map.exibirMapa();
    std::cout << "=== OPCOES ===\n";
    std::cout << "i. Abrir Inventario\n";
    std::cout << "s. Salvar Jogo\n";
    std::cout << "b. Voltar ao Menu\n";
}

void PlayingState::save(std::ostream& out) const {
    bag.save(out);
    cur_map.save(out);
    player.save(out);
}

void PlayingState::load(std::istream& in) {
    bag.load(in);
    cur_map.load(in);
    player.load(in);
}

bool PlayingState::shouldPop() {
    return exitRequested;
}