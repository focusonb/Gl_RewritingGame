#pragma once
class FileTextManager;
enum class FIleTextManager { Windows };

class FileManagerControler
{
public:
	FileManagerControler(FIleTextManager type = FIleTextManager::Windows);
	FileTextManager* getFileManager();
	~FileManagerControler();
	const char*  outPut();
private:
	FileTextManager* m_ptr_fileManager;
};

