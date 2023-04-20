#pragma once

class TextureManager
{
public:
	TextureManager();
	bool loadImage(const char* path, unsigned int& textureId);
	void setChannelType(int type);
private:
	int _ImageChannelType;
};

