#pragma once
#include <map>
#include <string>
#include "Texture.h"
#include "Shader.h"

#define SCREEN_START_WIDTH 960
#define SCREEN_START_HEIGHT 540


class Shader;

class ResourceManager {

public:

	// Access textures with their name
	static std::map<std::string, Texture> textureMap;
	static std::map<std::string, Shader> shaderMap;

	// For loading shaders and textures and storing them in their maps
	static void LoadTexture(const char* path, const std::string& name, bool alpha = false);
	static void LoadShader(const char* vertPath, const char* fragPath, const std::string &name);
	// Loads all the resources we need for the game
	static void LoadResources();

	// Stores key presses
	static bool keys[1024];

private:

	ResourceManager(){}

};