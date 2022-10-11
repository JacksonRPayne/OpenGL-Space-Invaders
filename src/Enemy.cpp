#include "Enemy.h"

Enemy::Enemy(const Texture& texture) : GameObject(texture) {

}
Enemy::Enemy(const Texture& texture, const glm::vec2& position, const glm::vec2& size, float rotation) :
    GameObject(texture, position, size, rotation){

}

void Enemy::Update(float dt) {
    Rotate(20.0f * dt);
}