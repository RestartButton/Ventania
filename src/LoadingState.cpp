#include <fstream>
#include "Game.hpp"
#include "LoadingState.hpp"

std::unique_ptr<PlayingState> LoadingState::carregarJogo(const std::string& nomeArquivo) {
    std::ifstream in(nomeArquivo, std::ios::binary);
    if (!in) {
        std::cerr << "Erro ao abrir arquivo para carregar.\n";
        return nullptr;
    }

    auto novoEstado = std::make_unique<PlayingState>();
    novoEstado->load(in);
    return novoEstado;
}

void LoadingState::handleInput(char input) {
    if (input == 'b') {
        std::cout << "-> Voltando para o Jogo...\n";
        exitRequested = true;
    } else if (input == '1' && std::ifstream("sav1.dat")) {
        system("cls");
        std::cout << "-> Carregando o Jogo...\n";
        if(!onMenu) {
            game->popState();
        }
        game->replaceState(carregarJogo("sav1.dat"));
        std::cout << "-> Jogo Carregado...\n";
        system("pause");
    } else if (input == '2' && std::ifstream("sav2.dat")) {
        system("cls");
        std::cout << "-> Carregando o Jogo...\n";
        if(!onMenu) {
            game->popState();
        }
        game->replaceState(carregarJogo("sav2.dat"));
        std::cout << "-> Jogo Carregado...\n";
        system("pause");
    } else if (input == '3' && std::ifstream("sav3.dat")) {
        system("cls");
        std::cout << "-> Carregando o Jogo...\n";
        if(!onMenu) {
            game->popState();
        }
        game->replaceState(carregarJogo("sav3.dat"));
        std::cout << "-> Jogo Carregado...\n";
        system("pause");
    }
}

void LoadingState::update() {}

void LoadingState::render() {
    std::cout << "=== CARREGANDO ===\n";

    std::cout << "1. " << (std::ifstream("sav1.dat") ? "Primeiro Slot" : "Vazio") << "\n";
    std::cout << "2. " << (std::ifstream("sav2.dat") ? "Segundo Slot" : "Vazio") << "\n";
    std::cout << "3. " << (std::ifstream("sav3.dat") ? "Terceiro Slot" : "Vazio") << "\n";
    std::cout << "b. Voltar\n";
}

bool LoadingState::shouldPop() { return exitRequested; }