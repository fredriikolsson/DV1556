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

Folder::Folder(Folder & anotherFolder)
{
    this->previousFolder = anotherFolder.previousFolder;
    this->folderPos = anotherFolder.folderPos;

    this->currentItemsInFolder = anotherFolder.currentItemsInFolder;
    this->folderSize = anotherFolder.folderSize;

    for(int i = 0; i < this->currentItemsInFolder; i++)
    {
        this->structure[i] = anotherFolder.structure[i];
    }
}

bool Folder::addFile(File * toAdd)
{
    bool canAddFile = false;
    
    this->structure[this->currentItemsInFolder++] = toAdd;
}

bool Folder::addFolder(Folder * toAdd)
{
    this->structure[this->currentItemsInFolder++] = toAdd;
}

void Folder::getFolderStructure(FileSystemObject ** array)
{
    for(int i = 0; i < this->getFolderSize(); i++)
    {
        array[i] = this->structure[i];
    }
}

int Folder::getPos() const
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

std::string Folder::getName () const
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