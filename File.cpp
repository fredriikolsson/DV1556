#include "File.h"

File::File(std::string name, std::string content, int pos)
	:FileSystemObject(name)
{
	this->bufferPos = pos;
	this->content = content;
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

std::string File::getContent() const
{
	return this->content;
}

// std::string File::getName() const
// {
//     return this->name;
// }

//void File::operator=(File & anotherFile)
//{
//	setName(anotherFile.getName());
//	this->bufferPos = anotherFile.bufferPos;
//	
//}
