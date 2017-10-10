#ifndef FILESYSTEMOBJECT_H
#define FILESYSTEMOBJECT_H

#include<string>

class FileSystemObject
{
private:

public:
    FileSystemObject();
    ~FileSystemObject();

    virtual int getValue();
    virtual int insertValue();

};

#endif // FILESYSTEMOBJECT_H
