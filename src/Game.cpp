#include <iostream>
#include <chrono>
#include <conio.h>
#include "Game.hpp"

void Game::pushState(std::unique_ptr<GameState> state) {
    state->setGame(this);
    states.push(std::move(state));
}

void Game::replaceState(std::unique_ptr<GameState> state) {
    popState();
    state->setGame(this);
    states.push(std::move(state));
}

void Game::popState() {
    if (!states.empty()) {
        states.pop();
    }
    if (states.empty()) {
        running = false;
    }
}

void Game::gameLoop() {
    using namespace std::chrono_literals;
    constexpr std::chrono::nanoseconds timestep(16ms);
    using clock = std::chrono::high_resolution_clock;
    
    std::chrono::nanoseconds lag(0ns);
    auto time_start = clock::now();

    while (running && !states.empty()) {
        auto current_time = clock::now();
        auto delta_time = current_time - time_start;
        time_start = current_time;
        lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

        auto& state = states.top();

        if (_kbhit()) {
            char input = _getch(); // Captura tecla pressionada sem Enter
            state->handleInput(input);
        }
        
        while(lag >= timestep) {
            lag -= timestep;

            state->update();
        }    
        system("cls");
        state->render();

        if (state->shouldPop()) {
            popState();
        }
        
    }
}