#include "Texture.h"

Texture::Texture() : texID(0), width(0), height(0), channels(0) {
	glGenTextures(1, &texID);
}

Texture::Texture(const char* path, bool png) : texID(0), width(0), height(0), channels(0) {
	glGenTextures(1, &texID);
	Load(path, png);
}

Texture::~Texture() {

}

// No support for texture slots (probably fine)
void Texture::Bind() const{
	glBindTexture(GL_TEXTURE_2D, texID);
}

void Texture::Load(const char* path, bool alpha) {
	// Load texture image
	unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
	// Checks for loading error
	if (!data) {
		std::cout << "ERROR: Could not load texture: " << path << std::endl;
		stbi_image_free(data);
		return;
	}
	// Load texture data into opengl and generate mipmaps (them tiny res textures)
	Bind();
	// Loads differently if theres an alpha channel
	if (alpha) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else { glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); }
	glGenerateMipmap(GL_TEXTURE_2D);
	// Sets texture parameters (hard coded for now)
	// Nearest filtering for minimizing and magnifying
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Repeat on in every direction
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Frees image data and unbinds texture
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}