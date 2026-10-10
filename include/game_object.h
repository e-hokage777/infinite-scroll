#include "glm/gtc/matrix_transform.hpp"
#include <string>
#include "shader.h"

class GameObject
{
public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec2 size = glm::vec2(1.0f);
    glm::mat4 modelMat = glm::mat4(1.0f);
    std::string name = "GameObject";

    GameObject() {}
    virtual ~GameObject() = default;

    virtual void Draw() {};
    virtual void Update(){};
};