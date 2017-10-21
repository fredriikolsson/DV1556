#ifndef FILE_H
#define FILE_H

#include "FileSystemObject.h"
#include <string>

class File : public FileSystemObject
{
private:
	int bufferPos;
public:
	File(std::string name, int pos = 0);
	~File();
	// File(File & anotherFile);
	File* File::clone() const;

	int getPos() const;
	// std::string getName() const;
};

#endif // File_H
