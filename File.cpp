#include "File.h"

File::File(std::string name, int pos)
	:FileSystemObject(name)
{
	this->bufferPos = pos;
}

File::~File()
{

}
File* File::clone() const
{
	return new File(*this);
}

// File::File(File & anotherFile)
// {
//     this->bufferPos = anotherFile.bufferPos;
// }

int File::getPos() const
{
	return this->bufferPos;
}

// std::string File::getName() const
// {
//     return this->name;
// }