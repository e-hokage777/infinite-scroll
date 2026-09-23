#include <sprite.h>
#include "glm/gtc/matrix_transform.hpp"
#include "input_manager.h"

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
    glm::mat4 modelMat = glm::mat4(1.0f);
    glm::mat4 projectionMat;

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

    void update(float deltaTime, InputManager *inputManager){
        if(inputManager->isKeyDown(GLFW_KEY_W)){
            this->state = State::FORWARD;
            this->x += 10 * deltaTime;
        }
        if(inputManager->isKeyDown(GLFW_KEY_S)){
            this->state = State::BACKWARD;
            this->x -= 10 * deltaTime;
        }
        if(inputManager->isKeyDown(GLFW_KEY_SPACE)){
            this->state = State::JUMP;
        }
        if(inputManager->isKeyDown(GLFW_KEY_C)){
            this->state = State::CROUCH;
        }
    }

    void render(Shader shader){
        this->modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(this->x, this->y, 0.0f));
        shader.use();
        shader.uniformMat4("model", this->modelMat);
        shader.uniformMat4("projection", this->projectionMat);

        this->sprite.Draw(shader);
    }
};