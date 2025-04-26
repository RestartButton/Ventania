#include "Entity.hpp"
#include "Serializable.hpp"

enum Key_code {
    ARROW_UP = 72,
    ARROW_DOWN = 80,
    ARROW_LEFT = 75,
    ARROW_RIGHT = 77
};

class Player : public Entity, public Serializable {
    int lifePoints = 10, maxLifePoints = 10;
    int direction = 1;
public:
    bool up = false, down = false, right = false, left = false;

    Player(float x, float y, int w, int h);

    void handleInput(char input);
    void update() override;
    void render() override;

    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};