#include <string>
#include <fstream>
#include "Game.hpp"
#include "SavingState.hpp"
#include "PlayingState.hpp"


void SavingState::salvarJogo(const PlayingState& state, const std::string& nomeArquivo) {
    std::ofstream out(nomeArquivo, std::ios::binary);
    if (!out) {
        std::cerr << "Erro ao abrir arquivo para salvar.\n";
        return;
    }
    state.save(out);
}

SavingState::SavingState(PlayingState& joj) : jogo(joj) {}

void SavingState::handleInput(char input) {
    if (input == 'b') {
        std::cout << "-> Voltando para o Jogo...\n";
        exitRequested = true;
    } else if (input == '1') {
        system("cls");
        std::cout << "-> Salvando o Jogo...\n";
        salvarJogo(jogo, "sav1.dat");
        std::cout << "-> Jogo Salvo...\n";
        system("pause");
    } else if (input == '2') {
        system("cls");
        std::cout << "-> Salvando o Jogo...\n";
        salvarJogo(jogo, "sav2.dat");
        std::cout << "-> Jogo Salvo...\n";
        system("pause");
    } else if (input == '3') {
        system("cls");
        std::cout << "-> Salvando o Jogo...\n";
        salvarJogo(jogo, "sav3.dat");
        std::cout << "-> Jogo Salvo...\n";
        system("pause");
    }
}

void SavingState::update() {}

void SavingState::render() {
    std::cout << "=== SALVANDO ===\n";
    std::cout << "1. " << (std::ifstream("sav1.dat") ? "Primeiro Slot" : "Vazio") << "\n";
    std::cout << "2. " << (std::ifstream("sav2.dat") ? "Segundo Slot" : "Vazio") << "\n";
    std::cout << "3. " << (std::ifstream("sav3.dat") ? "Terceiro Slot" : "Vazio") << "\n";
    std::cout << "b. Voltar\n";
}

bool SavingState::shouldPop() { return exitRequested; }
