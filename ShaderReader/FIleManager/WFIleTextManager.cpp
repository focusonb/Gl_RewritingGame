#include "WFIleTextManager.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

char* WFIleTextManager::outPut()
{
	std::string vertexCode;
	std::ifstream vShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(m_filePath);
		std::stringstream vShaderStream;
		/*-------------------------------------------------------------------------*/

		//stringstream sss("sdfsdfdsf");
		//ofstream oo;
		//oo.open(vertexPath);
		//sss >> oo.rdbuf();
		//return;

		/*--------------------------------------------------------------------------------*/
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();

		// close file handlers
		vShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return nullptr;
	}
	const char* vShaderCode = vertexCode.c_str();
	//std::cout <<"1"<<"\n"<< vShaderCode << std:: endl;
	if (m_shaderContent != nullptr)
	{
		delete[] m_shaderContent;
		m_shaderContent = nullptr;
	}
	m_textSize = strlen(vShaderCode) + 1;
	m_shaderContent = new char[m_textSize];

	strcpy_s(m_shaderContent, m_textSize, vShaderCode);
	return m_shaderContent;
}
WFIleTextManager::~WFIleTextManager()
{
	if (m_shaderContent != nullptr)
	{
		delete[] m_shaderContent;
	}
}

void FileTextManager::setFilePath(const char * filePath)
{
	m_filePath = filePath;
}
