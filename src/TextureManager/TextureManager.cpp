#include "TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../ThirdParty/Stb_image/stb_image.h"
#include <iostream>

//#include <glfw3.h>
#include <glad/glad.h>

TextureManager::TextureManager()
{
}

bool TextureManager::loadImage(const char * path, unsigned int& textureId)
{
	stbi_set_flip_vertically_on_load(true);
	// texture 1
	// ---------
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//get image data
	int width, height, nrChannels;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data == nullptr)
	{
		std::cout << "get image data failed" << std::endl;
		return false;
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, _ImageChannelType, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);
	return true;
}

void TextureManager::setChannelType(int type)
{
	_ImageChannelType = type;
}
