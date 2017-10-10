#ifndef FILE_H
#define FILE_H

#include "FileSystemObject.h"

class File : public FilesSystemObject
{
private:
    int bufferPos;
public:
    File(int pos);
    ~File();

    int getBufferPos();
};

#endif // File_H

#endif
