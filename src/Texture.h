#pragma once
#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <iostream>

class Texture 
{
public:

	Texture();
	// Loads from file while declaring
	//TODO: change png to alpha
	Texture(const char* path, bool alpha = false);
	~Texture();
	// Loads an image file
	void Load(const char* path, bool png=false);
	// Readies the texture to be used
	void Bind() const;

	// Width and height data for image and number of color channels
	int width, height, channels;
private:
	// Opengl id for texture
	unsigned int texID;

};