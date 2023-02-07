#include "Enemy.h"

// Initialize static vector
std::vector<Enemy*> Enemy::Enemies = std::vector<Enemy*>();

Enemy::Enemy(const Texture& texture) : GameObject(texture), animator(), dead(false) {
    InitializeAnimations();
}
Enemy::Enemy(const Texture& texture, const glm::vec2& position, const glm::vec2& size, float rotation) :
    GameObject(texture, position, size, rotation), animator(), dead(false) {
    InitializeAnimations();
}

void Enemy::InitializeAnimations() {
    Animation idle(std::vector<Texture>{ResourceManager::textureMap["Ethan"]}, 2.0f);
    Animation die(std::vector<Texture>{ResourceManager::textureMap["EthanDead"]}, 2.0f);
    animator.AddAnimation("Idle", idle);
    animator.AddAnimation("Die", die);
    animator.PlayAnimation("Idle", true, true);
}

Enemy::~Enemy() {
    // Finds this object in enemies list and removes it
    for (int i = 0; i < Enemies.size(); i++) {
        if (Enemies[i] == this) {
            Enemies.erase(Enemies.begin() + i);
            return;
        }
    }
}

void Enemy::Kill() {
    if (dead) return;
    animator.PlayAnimation("Die", false, false);
    dead = true;
}

void Enemy::Update(float dt) { 
    Translate(glm::vec2(sin(2*glfwGetTime())*10*dt, 0));
    animator.Update(dt);
    SetTexture(animator.GetCurrentFrame());
    if (dead && !animator.PlayingAnimation()) delete this;
}