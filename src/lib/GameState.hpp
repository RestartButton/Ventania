#pragma once

class Game;

class GameState {
protected:
    Game* game;
public:
    virtual ~GameState() {}
    virtual void handleInput(char input) = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual bool shouldPop() { return false; } // indica se o estado deve ser removido

    void setGame(Game* g) { game = g; }
};