#include "GameObject.h"

// Stores all game objects in scene
std::vector<GameObject*> GameObject::GameObjects = std::vector<GameObject*>();

GameObject::GameObject(): texture(), position(), size(), rotation(0){}

GameObject::GameObject(const Texture &texture) : position(), size(), rotation(0) {
	this->texture = texture;
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

}

void GameObject::Render(const SpriteRenderer &renderer) {
	renderer.Render(texture, position, size, rotation);
}

void GameObject::Update(float dt) {
	// Overriden with behaviour
}