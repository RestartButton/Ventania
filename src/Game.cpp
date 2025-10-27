#include <iostream>
#include <chrono>
#ifdef _WIN32
    #include <conio.h>
#elif __linux__
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif
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

#ifdef __linux__
    // Função para configurar o terminal no modo raw
    void setTerminalRawMode(bool enable) {
        static struct termios oldt, newt;
        if (enable) {
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO); // Desliga buffer de linha e eco
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        } else {
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        }
    }

    // Função para verificar se uma tecla foi pressionada
    bool kbhit() {
        int old_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, old_flags | O_NONBLOCK);

        int ch = getchar();

        fcntl(STDIN_FILENO, F_SETFL, old_flags);

        if (ch != EOF) {
            ungetc(ch, stdin);
            return true;
        }

        return false;
    }

    // Função para ler um caractere sem precisar de Enter
    char getch() {
        char buf = 0;
        read(STDIN_FILENO, &buf, 1);
        return buf;
    }
#endif

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

        #ifdef _WIN32
            if (_kbhit()) {
                char input = _getch(); // Captura tecla pressionada sem Enter
                if (input == 0 || input == 224)
                    input = _getch(); // Captura o real código se for tecla especial
                state->handleInput(input);
            }
        #elif __linux__
            setTerminalRawMode(true);
            if (kbhit()) {
                char input = getch();
                // No Linux, teclas especiais são sequências (começam com 27 - ESC)
                if (input == 27) { // Tecla especial detectada (ESC sequence)
                    getch(); // Pula '['
                    input = getch(); // Captura o real código
                }
                state->handleInput(input);
            }
            setTerminalRawMode(false);
        #endif
        
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