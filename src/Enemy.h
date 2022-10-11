#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(const Texture& texture);
	Enemy(const Texture& texture, const glm::vec2& position, const glm::vec2& size, float rotation);


	void Update(float dt);
};

