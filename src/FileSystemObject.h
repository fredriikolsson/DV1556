#ifndef FILESYSTEMOBJECT_H
#define FILESYSTEMOBJECT_H

#include <string>

class FileSystemObject
{
private: 
    std::string name;
public:

    FileSystemObject(std::string name) {this->name = name;}
    virtual ~FileSystemObject() {};    

    virtual std::string getName() {return this->name;}
};

#endif // FILESYSTEMOBJECT_H
