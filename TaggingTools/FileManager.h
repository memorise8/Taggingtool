#pragma once
class FileManager
{
public:
	FileManager();
	~FileManager() {}
	FileManager(const char* path);
	void Read();
	void Read(int flag);
	void Read(int flag, std::string extension);
	void Write();
	bool isWork();

	int frameNum;
private:

	bool readFileFlag;
	bool writeFileFlag;
	std::string path;
	std::vector<std::string> vecFileList;
};

