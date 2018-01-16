#include "stdafx.h"

#include <io.h>

#include "FileManager.h"

FileManager::FileManager()
	: readFileFlag(false)
	, writeFileFlag(false)
	, frameNum(0)
{

}
FileManager::FileManager(const char* path)
	: readFileFlag(false)
	, writeFileFlag(false)
	, frameNum(0)
{
	
	this->path = path;
	

}

void FileManager::Read(int flag, std::string extension) // read all file with extension & flag
{
	this->path += "*." + extension;
	Read();
}

void FileManager::Read(int flag) // read all file with flag
{
	this->path += "/*.*";
	Read();
}

void FileManager::Read() // read all file
{

#ifdef WIN64

	struct _finddata_t fd;

	intptr_t handle;

	if ((handle = _findfirst(path.c_str(), &fd)) == -1L)
	{
		std::cout << "No file in directory!" << std::endl;
		return;
	}

	int result = 0;
	while (result == 0)
	{
		if (fd.attrib & _A_SUBDIR)
		{

		}
		else if (fd.attrib & _A_HIDDEN)
		{
			
		}
		else
		{
			std::string temp = fd.name;

#if _DEBUG
			std::cout << temp << std::endl;
#endif // _DEBUG

			
			this->vecFileList.push_back(temp);
		}
		result = _findnext(handle, &fd);
	}

	_findclose(handle);
#endif // WIN64

}

void FileManager::Write()
{
	char fileName[200];
	sprintf_s(fileName, "%d", frameNum);

	std::string strFileName = fileName;
	
	frameNum++;
}

bool FileManager::isWork()
{
	
	if (readFileFlag || writeFileFlag)
	{
		return true;
	}
	else
		return false;
}