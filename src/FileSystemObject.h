#ifndef FILESYSTEMOBJECT_H
#define FILESYSTEMOBJECT_H

#include <string>

class FileSystemObject
{
public:
    FileSystemObject();
    virtual ~FileSystemObject();

    virtual int getPos() const = 0;
};

#endif // FILESYSTEMOBJECT_H
