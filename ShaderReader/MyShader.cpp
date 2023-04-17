#include "MyShader.h"
#include <iostream>
#include <glad/glad.h>
#include "FIleManager/WFIleTextManager.h"

MyShader::MyShader(const char * filePath, const char * filePath2, FIleTextManager type)
	:m_ptr_controler(new FileManagerControler(type))
{
	FileTextManager* textManager = m_ptr_controler->getFileManager();
	textManager->setFilePath(filePath);
	unsigned int vertexShader = loadShader(filePath, GL_VERTEX_SHADER);
	textManager->setFilePath(filePath2);
	unsigned int fragmentShader = loadShader(filePath2, GL_FRAGMENT_SHADER);
	if (vertexShader == 0 || fragmentShader == 0) {
		std::cout << "load shader failed" << std::endl;
		m_shaderProgram = 0;
		return;
	}
	//link shader
	if (m_shaderProgram == 0)
		m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragmentShader);
	glLinkProgram(m_shaderProgram);
	int success;
	char infoLog[512];
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADERPROGRAM::FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

int MyShader::getUniform(const char * uniformName)
{
	return glGetUniformLocation(m_shaderProgram, uniformName);
}

unsigned int MyShader::getShaderProgram()
{
	return m_shaderProgram;
}

unsigned int MyShader::loadShader(const char * filePath, int shaderType, FIleTextManager type)
{
	const char *shaderSource = m_ptr_controler->outPut();
	if (shaderSource == nullptr)
	{
		std::cout << "ERROR::GET_SHADERSOURCE_FAILED\n" << std::endl;
		return 0;
	}
	unsigned int shader;
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	//check shader compilation
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader;
}

