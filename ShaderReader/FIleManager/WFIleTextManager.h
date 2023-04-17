#pragma once
#include <cstring>
#include <iostream>

class FileTextManager
{
public:
	FileTextManager() :m_filePath()
	{};
	void setFilePath(const char* filePath);
	virtual  char* outPut() = 0;
	virtual ~FileTextManager() {};
protected:
	const char* m_filePath;
};
class WFIleTextManager : public FileTextManager
{
public:
	WFIleTextManager() :FileTextManager()
	{};
	virtual ~WFIleTextManager();
	char* outPut() override;
private:
	char* m_shaderContent;
	size_t m_textSize;
};

