#pragma once
#include "Texture.h"
#include "SpriteRenderer.h"
#include "glm/glm.hpp"
#include <vector>


class GameObject {

public:
	// Constructors/destructors
	GameObject();
	GameObject(const Texture &texture);
	GameObject(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size, float rotation);
	~GameObject();
	
	// Called every frame
	virtual void Render(const SpriteRenderer &renderer);
	virtual void Update(float dt);

	// Setters for private members
	void SetPosition(const glm::vec2 &newPos) { position = newPos; }
	void SetSize(const glm::vec2 &newSize) { size = newSize; }
	void SetRotation(float newRot) { rotation = newRot; }
	void SetTexture(const Texture &newTex) { texture = newTex; }
	// Getters for private members
	const glm::vec2& GetPosition() { return position; }
	const glm::vec2& GetSize() { return size; }
	float GetRotation() { return rotation; }
	const Texture& GetTexture() { return texture; }

	// For modifying transform 
	void Translate(const glm::vec2 &translation) { position += translation; }
	void Resize(const glm::vec2 &resizing) { size += resizing; }
	void Rotate(float rotation) { this->rotation += rotation; }

	// Checks collisions with AABB logic
	bool IsColliding(const glm::vec2& otherPos, const glm::vec2& otherSize);

	// Stores all game objects in scene
	static std::vector<GameObject*> GameObjects;

private:

	Texture texture;
	// Transform
	glm::vec2 position, size;
	float rotation;
};


