#pragma once
#include "FIleManager/FileManagerControler.h"
class FileManagerControler;
class MyShader
{
public:
	MyShader(const char* filePath, const char * filePath2, FIleTextManager type = FIleTextManager::Windows);
	~MyShader() { delete m_ptr_controler; };
	int getUniform(const char*	uniformName);
	unsigned int getShaderProgram();
private:
	FileManagerControler* m_ptr_controler;
	unsigned int m_shaderProgram = 0;
	unsigned int loadShader(const char* filePath, int shaderType, FIleTextManager type = FIleTextManager::Windows);
};
