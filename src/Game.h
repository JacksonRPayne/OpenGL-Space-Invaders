#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "SpriteRenderer.h"
#include <stb_image/stb_image.h>
#include "ResourceManager.h"
#include <vector>
#include "GameObject.h"
#include "Enemy.h"
#include "Player.h"


class Game
{
public:

	Game(unsigned int width, unsigned int height);
	~Game();
	// Starts main game loop
	void Run(const char* title);

private:
	unsigned int width, height;
	// Does the frames rendering
	void Render(const SpriteRenderer &renderer);
	// Updates all gameobjects
	void Update(float dt);
	// Sets up glfw and glad
	void InitializeWindow(GLFWwindow* window);
};

