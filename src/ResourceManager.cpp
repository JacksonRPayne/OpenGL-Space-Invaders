#include "ResourceManager.h"

// Declares maps
std::map<std::string, Texture> ResourceManager::textureMap;
std::map<std::string, Shader> ResourceManager::shaderMap;

// Initializes keys to all false
bool ResourceManager::keys[1024] = { 0 };

void ResourceManager::LoadTexture(const char* path, const std::string &name, bool alpha) {
	Texture texture(path, alpha);
	textureMap[name] = texture;
}

void ResourceManager::LoadShader(const char* vertPath, const char* fragPath, const std::string &name) {
	Shader shader(vertPath, fragPath);
	shaderMap[name] = shader;
}

void ResourceManager::LoadResources() {
	// Shaders
	ResourceManager::LoadShader("res/shaders/default.vert", "res/shaders/default.frag", "default");
	// Textures
	ResourceManager::LoadTexture("res/textures/Mike.jpg", "Mike");
	ResourceManager::LoadTexture("res/textures/Mike2.jpg", "Mike2");
	ResourceManager::LoadTexture("res/textures/Mike_Shoot.jpg", "MikeShoot");
	ResourceManager::LoadTexture("res/textures/Ethan.JPG", "Ethan");
	ResourceManager::LoadTexture("res/textures/EthanDead.JPG", "EthanDead");
	ResourceManager::LoadTexture("res/textures/bullet.png", "Bullet", true);
}