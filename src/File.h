#ifndef FILE_H
#define FILE_H

#include "FileSystemObject.h"
#include <string>

class File : public FileSystemObject
{
private: 
    int bufferPos;
    std::string fileName;
public:
    File(std::string name, int pos = 0);
    ~File();
    File(File & anotherFile);

    int getPos() const;
    std::string getName() const;
};

#endif // File_H
