#include <utility>
#include "Map.hpp"

class Entity {
protected:
    float posX, posY;
    int width, height;
    float speed;
public:
    Map* map;

    Entity(float x, float y, int w, int h, float s = 1.0f) 
        : posX(x), posY(y), width(w), height(h), speed(s) {}

    virtual void update() = 0;
    virtual void render() = 0;

    const std::pair<float, float> getPos() { return {posX, posY}; }
};