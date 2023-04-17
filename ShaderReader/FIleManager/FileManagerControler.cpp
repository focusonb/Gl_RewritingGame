#include "FileManagerControler.h"
#include "WFIleTextManager.h"

FileManagerControler::FileManagerControler(FIleTextManager type)
{
	switch (type)
	{
	case FIleTextManager::Windows:
		m_ptr_fileManager = new WFIleTextManager();
	}
}

FileTextManager * FileManagerControler::getFileManager()
{
	return m_ptr_fileManager;
}

FileManagerControler::~FileManagerControler()
{
	delete m_ptr_fileManager;
}

const char * FileManagerControler::outPut()
{
	return m_ptr_fileManager->outPut();
}
