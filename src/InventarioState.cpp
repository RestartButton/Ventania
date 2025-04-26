#include <iostream>
#include "InventarioState.hpp"

InventarioState::InventarioState(Inventario& inv) : bag(inv) {}

void InventarioState::handleInput(char input) {
    if (input == '1') {
        Item espada("Espada", "Uma espada afiada", 1, 1);
        bag.adicionarItem(espada);
    } else if (input == '2') {
        Item pocao("Pocao", "Uma pocao azul", 2, 1);
        bag.adicionarItem(pocao);
    } else if (input == 'b') {
        std::cout << "-> Voltando para o Jogo...\n";
        exitRequested = true;
    }
}
void InventarioState::update() {}

void InventarioState::render() {
    std::cout << "=== INVENTARIO ===\n";
    bag.exibirInventario();
    std::cout << "=== OPCOES ===\n";
    std::cout << "1. Adicionar Espada\n";
    std::cout << "2. Adicionar Pocao\n";
    std::cout << "b. Voltar\n";
}

bool InventarioState::shouldPop() {
    return exitRequested;
}
