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

	std::string getName() const { return this->name; }
	void setName(std::string name) { this->name = name; }
	virtual FileSystemObject* clone() const = 0;

};

#endif // FILESYSTEMOBJECT_H
