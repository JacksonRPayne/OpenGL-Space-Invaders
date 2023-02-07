#pragma once
#include "Shader.h"
#include "Texture.h"
#include "ResourceManager.h"

class SpriteRenderer
{
public:

	// Projection matrix
	static glm::mat4 projection;

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

