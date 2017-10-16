#ifndef FILE_H
#define FILE_H

#include "FileSystemObject.h"

class File : public FileSystemObject
{
private: 
    int bufferPos;
public:
    File(int pos = 0);
    ~File();
    File(File & anotherFile);

    int getBufferPos();
};

#endif // File_H
