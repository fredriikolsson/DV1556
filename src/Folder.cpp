#include "Folder.h"

Folder::Folder(int previousFolder, int folderPos, std::string folderName)
{
    this->previousFolder = previousFolder;
    this->folderPos = folderPos;

    this->currentItemsInFolder = 0;
    this->folderSize = 10;
    this->structure = new FileSystemObject * [this->folderSize];

}

Folder::~Folder() {
    for(int i = 0; i < this->currentItemsInFolder; i++)
    {
        delete this->structure[i];
    }
    delete [] this->structure;
}

void Folder::getFolderStructure(FileSystemObject ** array)
{
    for(int i = 0; i < this->getFolderSize(); i++)
    {
        array[i] = this->structure[i];
    }
}

int Folder::getFolderPos() const
{
    return this->folderPos;
}

int Folder::getPrevousFolder() const
{
    return this->previousFolder;
}

int Folder::getFolderSize() const
{
    return this->currentItemsInFolder;
}

std::string Folder::getFolderName () const
{
    return this->folderName;
}

void Folder::expandFolder()
{
    this->folderSize = this->folderSize + 10;
    FileSystemObject ** temp = new FileSystemObject * [this->folderSize];

    for(int i = 0; i < this->currentItemsInFolder; i++)
    {
        temp[i] = this->structure[i];
    }

    delete [] this->structure;

    this->structure = temp; 
}