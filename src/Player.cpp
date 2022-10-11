#include "Player.h"

// Specify to call superclass constructor 
Player::Player(const Texture& texture) : GameObject(texture), moveSpeed(200.0f) {

}
Player::Player(const Texture& texture, const glm::vec2& position, const glm::vec2& size, float rotation) :
    GameObject(texture, position, size, rotation), moveSpeed(200.0f) {

}

void Player::Update(float dt) {

	// Do something every frame
    if (ResourceManager::keys[GLFW_KEY_RIGHT]) {
        Translate(glm::vec2(moveSpeed * dt, 0));
    }
    else if (ResourceManager::keys[GLFW_KEY_LEFT]) {
        Translate(glm::vec2(-moveSpeed * dt, 0));
    }
    if (ResourceManager::keys[GLFW_KEY_UP]) {
        Translate(glm::vec2(0, -moveSpeed * dt));
    }
    else if (ResourceManager::keys[GLFW_KEY_DOWN]) {
        Translate(glm::vec2(0, moveSpeed * dt));
    }
    if (ResourceManager::keys[GLFW_KEY_SPACE]) {
        std::cout << GetRotation() << std::endl;
        Rotate(50.0f*dt);
    }

}