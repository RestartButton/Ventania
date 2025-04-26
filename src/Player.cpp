#include "Player.hpp"

Player::Player(float x, float y, int w, int h)
    : Entity(x,y,w,h,1.0f) {};

void Player::handleInput(char input) {
    switch(input) {
        case ARROW_UP:
            up = true;
            break;
        case ARROW_DOWN:
            down = true;
            break;
        case ARROW_LEFT:
            left = true;
            break;
        case ARROW_RIGHT:
            right = true;
            break;
    }
}

void Player::update() {
    if(up) 
        posY -= speed;
    if(down)
        posY += speed;
    if(left)
        posX -= speed;
    if(right)
        posX += speed;

    if(posY < 0)
        posY = 0;
    if(posX < 0)
        posX = 0;
    if(posY + height >= map->getHeight())
        posY = map->getHeight() - height - 1;
    if(posX + width >= map->getWidth())
        posX = map->getWidth() - width - 1;

    if(lifePoints < 0)
        lifePoints = 0;

    up = false;
    down = false;
    left = false;
    right = false;
}

void Player::render() {}

void Player::save(std::ostream& out) const {
    // Salvar atributos de vida
    out.write(reinterpret_cast<const char*>(&lifePoints), sizeof(lifePoints));
    out.write(reinterpret_cast<const char*>(&maxLifePoints), sizeof(maxLifePoints));
    out.write(reinterpret_cast<const char*>(&direction), sizeof(direction));

    // Salvar movimentos
    out.write(reinterpret_cast<const char*>(&up), sizeof(up));
    out.write(reinterpret_cast<const char*>(&down), sizeof(down));
    out.write(reinterpret_cast<const char*>(&right), sizeof(right));
    out.write(reinterpret_cast<const char*>(&left), sizeof(left));

    // Se a Entity base (posição x, y, w, h) precisa ser salva, adiciona aqui:
    out.write(reinterpret_cast<const char*>(&posX), sizeof(posX));
    out.write(reinterpret_cast<const char*>(&posY), sizeof(posY));
    out.write(reinterpret_cast<const char*>(&width), sizeof(width));
    out.write(reinterpret_cast<const char*>(&height), sizeof(height));
    out.write(reinterpret_cast<const char*>(&speed), sizeof(speed));
}

void Player::load(std::istream& in) {
    // Carregar atributos de vida
    in.read(reinterpret_cast<char*>(&lifePoints), sizeof(lifePoints));
    in.read(reinterpret_cast<char*>(&maxLifePoints), sizeof(maxLifePoints));
    in.read(reinterpret_cast<char*>(&direction), sizeof(direction));

    // Carregar movimentos
    in.read(reinterpret_cast<char*>(&up), sizeof(up));
    in.read(reinterpret_cast<char*>(&down), sizeof(down));
    in.read(reinterpret_cast<char*>(&right), sizeof(right));
    in.read(reinterpret_cast<char*>(&left), sizeof(left));

    // Carregar Entity base (posição x, y, w, h)
    in.read(reinterpret_cast<char*>(&posX), sizeof(posX));
    in.read(reinterpret_cast<char*>(&posY), sizeof(posY));
    in.read(reinterpret_cast<char*>(&width), sizeof(width));
    in.read(reinterpret_cast<char*>(&height), sizeof(height));
    in.read(reinterpret_cast<char*>(&speed), sizeof(speed));
}
