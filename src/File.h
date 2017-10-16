#ifndef FILE_H
#define FILE_H

#include "FileSystemObject.h"

class File : public FileSystemObject
{
public:
    File(int pos = 0);
    ~File();

    int getBufferPos();
};

#endif // File_H
