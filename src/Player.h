#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Projectile.h"
#include "Animator.h"

class Player : public GameObject {

public:
	Player(const Texture& texture);
	Player(const Texture& texture, const glm::vec2& position, const glm::vec2& size, float rotation);

	void Update(float dt);

private:

	float moveSpeed;
	std::vector<Projectile*> projectiles;
	void DestroyProjectiles();

	Animator animator;
	void InitializeAnimations();
};