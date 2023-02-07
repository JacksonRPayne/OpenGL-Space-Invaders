#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GameObject.h"
#include "Enemy.h"

class Projectile : public GameObject
{
public:
	float speed; 

	Projectile(const Texture& texture, const glm::vec2& position, const glm::vec2& size, float rotation) :
		GameObject(texture, position, size, rotation), speed(500.0f) {

	}
	void Update(float dt) {
		Translate(glm::vec2(0.0f, -speed * dt));
		for (int i = 0; i < Enemy::Enemies.size(); i++) {
			if (IsColliding(Enemy::Enemies[i]->GetPosition(), Enemy::Enemies[i]->GetSize())) {
				Enemy::Enemies[i]->Kill();
			}
		}
	}
};

