#ifndef FILESYSTEMOBJECT_H
#define FILESYSTEMOBJECT_H

#include <string>

class FileSystemObject
{
private:
    int pos;
public:
    FileSystemObject(int pos) { this->pos = pos;};
    virtual ~FileSystemObject() {} const = 0;

    virtual int getPos() const;
};

#endif // FILESYSTEMOBJECT_H
