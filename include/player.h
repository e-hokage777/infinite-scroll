#include <sprite.h>

class Player
{
public:
    enum class State
    {
        IDLE = 0,
        FORWARD = 1,
        BACKWARD = 2,
        JUMP = 3,
        CROUCH = 4
    };

    Sprite sprite;
    int x, y;
    State state = State::IDLE;

    Player(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    void move(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};