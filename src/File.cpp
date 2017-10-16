#include "File.h"

File::File(int pos) 
{
    this->bufferPos = pos;
}

File::~File()
{

}

int File::getBufferPos()
{
    return this->bufferPos;
}