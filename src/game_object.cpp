#include "game_object.h"
#include "sprite_renderer.h"
#include "timer.h";

GameObject::GameObject()
    : position(0.0f, 0.0f), size(1.0f, 1.0f), velocity(0.0f), color(1.0f), rotation(0.0f), sprite(), isSolid(false), isDestroyed(false) {}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture sprite, glm::vec3 color, glm::vec2 velocity, glm::vec2 acceleration)
    : position(pos), size(size), velocity(velocity), acceleration(acceleration), color(color), rotation(0.0f), sprite(sprite), isSolid(false), isDestroyed(false) {}

void GameObject::Update()
{
    // velocity += acceleration * Time::deltaTime;
    // position += velocity;
}

void GameObject::Draw()
{
    SpriteRenderer::Draw(this->sprite, this->position, this->size, this->rotation);
}
