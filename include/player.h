#include <vector>
#include "glm/gtc/matrix_transform.hpp"
#include "input_manager.h"
#include "sprite.h"

class Player
{
private:
    Shader shader;

public:
    enum class State
    {
        IDLE,
        JUMP,
        FALL,
        RUN,
        STUPOR,
        CROUCH,
        ROLL,
    };

    struct AnimState
    {
        int stateIndex;
        int frameCount;
    };

    Sprite sprite;
    float x, y;
    State state = State::IDLE;
    glm::mat4 modelMat = glm::mat4(1.0f);
    std::vector<AnimState> states;

    Player() {};
    Player(float x, float y)
    {
        this->x = x;
        this->y = y;
        this->shader = Shader("shaders/sprite.vs", "shaders/sprite.fs");
        this->sprite = Sprite(40.0f, 40.0f, "assets/shadow_dog.png", 10, 12);

        // setting up states
        this->states = {
            {0, 7},
            {1, 7},
            {2, 7},
            {3, 9},
            {4, 11},
            {5, 5},
            {6, 7}};
    }

    void move(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    void update(float deltaTime, InputManager *inputManager)
    {
        if (inputManager->isKeyDown(GLFW_KEY_D))
        {
            this->state = State::RUN;
            this->x += 20 * deltaTime;
        }
        if (inputManager->isKeyDown(GLFW_KEY_A))
        {
            this->state = State::RUN;
            this->x -= 10 * deltaTime;
        }
        if (inputManager->isKeyDown(GLFW_KEY_SPACE))
        {
            this->state = State::JUMP;
        }
        if (inputManager->isKeyDown(GLFW_KEY_C))
        {
            this->state = State::CROUCH;
        }

        this->sprite.setState(this->states[(int)this->state].stateIndex, this->states[(int)this->state].frameCount);

        this->sprite.Update(deltaTime);
    }

    void render(glm::mat4 projectionMat)
    {
        this->modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(this->x, this->y, 0.0f));
        shader.use();
        shader.uniformMat4("model", this->modelMat);
        shader.uniformMat4("projection", projectionMat);

        this->sprite.Draw(shader);
    }
};