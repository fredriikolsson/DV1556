#ifndef FILE_H
#define FILE_H

#include "FileSystemObject.h"
#include <string>

class File : public FileSystemObject
{
private:
	int bufferPos;
	std::string content;
public:
	File(std::string name, std::string content = "Empty", int pos = 0);
	~File();
	// File(File & anotherFile);
	File* File::clone() const;

	int getPos() const;
	std::string getContent() const;
	// void File::operator=(File & anotherFile);
	// std::string getName() const;
};
#endif // File_H
