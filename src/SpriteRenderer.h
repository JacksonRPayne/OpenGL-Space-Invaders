#pragma once
#include "Shader.h"
#include "Texture.h"

class SpriteRenderer
{
public:
	// Must pass a shader to render sprite
	SpriteRenderer(Shader &shader);
	~SpriteRenderer();

	void Render(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size, float rotate) const;

private:
	// Stores the shader
	Shader shader;
	// Stores the opengl id of the VAO
	unsigned int VAO;
};

