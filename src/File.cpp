#include "File.h"

File::File(std::string name, int pos)
{
    this->bufferPos = pos;
    this->fileName = name;
}

File::~File()
{

}

File::File(File & anotherFile)
{
    this->bufferPos = anotherFile.bufferPos;
}

int File::getPos() const
{
    return this->bufferPos;
}

std::string File::getName() const
{
    return this->fileName;
}