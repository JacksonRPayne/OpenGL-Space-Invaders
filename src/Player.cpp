#include "Player.h"

// Specify to call superclass constructor 
Player::Player(const Texture& texture) : GameObject(texture), moveSpeed(200.0f), animator() {
    InitializeAnimations();
}
Player::Player(const Texture& texture, const glm::vec2& position, const glm::vec2& size, float rotation) :
    GameObject(texture, position, size, rotation), moveSpeed(200.0f), animator() {
    InitializeAnimations();
}

void Player::InitializeAnimations() {
    // Passing by const reference, will this segfault?
    Animation idle(std::vector<Texture>{ResourceManager::textureMap["Mike"], ResourceManager::textureMap["Mike2"]}, 2.0f);
    Animation shoot(std::vector<Texture>{ResourceManager::textureMap["MikeShoot"]}, 2.0f);
    animator.AddAnimation("Idle", idle);
    animator.AddAnimation("Shoot", shoot);
    animator.PlayAnimation("Idle", true, true);
}

void Player::DestroyProjectiles() {
    // Finds any projectile that are out of sight and destroys them
    // TODO: Maybe replace with some sort of even so it doesn't have to keep checking all projectiles
    // I guess thats kinda the same anyway
    for (int i = 0; i < projectiles.size(); i++) {
        if (projectiles[i]->GetPosition().y < 0) {
            delete projectiles[i];
            projectiles.erase(projectiles.begin() + i);
        }
    }
}

bool prevSpace;

void Player::Update(float dt) {
    // Destroys projectiles that are out of sight
    DestroyProjectiles();
    // Shoots bullet
    if (ResourceManager::keys[GLFW_KEY_SPACE]&& !prevSpace) {
        // Adds a new projectile to the projectiles list
        Projectile* projectile = new Projectile(ResourceManager::textureMap["Bullet"], GetPosition() - glm::vec2(0,GetSize().y), glm::vec2(50.0f, 50.0f), -90.0f);
        projectiles.push_back(projectile);
        if (!prevSpace) {
            animator.PlayAnimation("Shoot", false, false);
            animator.PlayOnce("Idle", true, true);
        }
    }

    prevSpace = ResourceManager::keys[GLFW_KEY_SPACE];
    // Move left and right
    if (!(GetPosition().x < GetSize().x / 2 )&& ResourceManager::keys[GLFW_KEY_LEFT]) {
        Translate(glm::vec2(-moveSpeed * dt, 0));
    }
    else if (!(GetPosition().x > 800 - GetSize().x / 2) && ResourceManager::keys[GLFW_KEY_RIGHT]) {
        Translate(glm::vec2(moveSpeed * dt, 0));
    }
    // TODO: make an inheritable AnimatedGameObject class that does all this stuff automatically
    animator.Update(dt);
    SetTexture(animator.GetCurrentFrame());
}