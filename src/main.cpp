#include <iostream>
#include <fstream>
#include "Game.hpp"
#include "MenuState.hpp"

int main() {
    Game game;
    game.pushState(std::make_unique<MenuState>());
    game.gameLoop();
    std::cout << "Jogo encerrado!\n";
    return 0;
}
