#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ResourceManager.h"
#include "GameObject.h"
#include "Animator.h"
#include <vector>

class Enemy : public GameObject
{
public:

	Enemy(const Texture& texture);
	Enemy(const Texture& texture, const glm::vec2& position, const glm::vec2& size, float rotation);
	~Enemy();
	// Kills the enemy
	void Kill();

	// Stores all enemies in the scene
	static std::vector<Enemy*> Enemies;

	void Update(float dt);

private:

	Animator animator;
	void InitializeAnimations();
	bool dead;
};

