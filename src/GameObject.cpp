#include "GameObject.h"

// Stores all game objects in scene
std::vector<GameObject*> GameObject::GameObjects = std::vector<GameObject*>();

GameObject::GameObject(): texture(), position(), size(), rotation(0){}

GameObject::GameObject(const Texture &texture) : position(), rotation(0) {
	this->texture = texture;
	// Defaultly sets size as size of texture
	size = glm::vec2(texture.width, texture.height);
	// Adds to list of gameobjects
	GameObjects.push_back(this);
}

GameObject::GameObject(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size, float rotation) {
	this->texture = texture;
	this->position = position;
	this->size = size;
	this->rotation = rotation;
	// Adds to list of gameobjects
	GameObjects.push_back(this);
}

GameObject::~GameObject() {
	// Finds this object in the gameobjects list and removes it
	for (int i = 0; i < GameObjects.size(); i++) {
		if (GameObjects[i] == this) {
			GameObjects.erase(GameObjects.begin() + i);
			return;
		}
	}
}

bool GameObject::IsColliding(const glm::vec2& otherPos, const glm::vec2& otherSize) {
	// Checks for x overlap (xpos of right side of this is greater than left side of other
	// and right side of other is greater than left side of this)
	bool xoverlap = (position.x + size.x / 2 >= otherPos.x - otherSize.x / 2) &&
		(otherPos.x + otherSize.x / 2 >= position.x - size.x / 2);
	// Checks for y overlap (you figure it out if you really want)
	bool yoverlap = (position.y + size.y / 2 >= otherPos.y - otherSize.y / 2) &&
		(otherPos.y + otherSize.y / 2 >= position.y - size.y / 2);
	// If both x and y are overlapping, there is a collision
	return xoverlap && yoverlap;
}

void GameObject::Render(const SpriteRenderer &renderer) {
	renderer.Render(texture, position, size, rotation);
}

void GameObject::Update(float dt) {
	// Overriden with behaviour
}