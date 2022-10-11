#pragma once
#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <iostream>

class Texture 
{
public:

	Texture();
	// Loads from file while declaring
	Texture(const char* path);
	~Texture();
	// Loads an image file
	void Load(const char* path);
	// Readies the texture to be used
	void Bind() const;

private:
	// Opengl id for texture
	unsigned int texID;
	// Width and height data for image and number of color channels
	int width, height, channels;
};