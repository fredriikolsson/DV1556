#include "File.h"

File::File(int pos):FileSystemObject(pos) 
{
    
}

File::~File()
{

}

File::File(File & anotherFile)
{
    this->bufferPos = anotherFile.pos;
}

int File::getBufferPos()
{
    return this->bufferPos;
}