#include "filesystem.h"

FileSystem::FileSystem() {
    this->mMemblockDevice = MemBlockDevice();
    this->blocks = 0;

    this->folders = new int[5];
}

FileSystem::~FileSystem() {

}


/* Please insert your code */
bool FileSystem::createFile(std::string fileName) {

        bool didCreate = false;
        bool exists = false;

        fileName.resize(512);

        for(int i = 0; i < this->blocks; i++)
        {
            exists = this->mMemblockDevice.readBlock(i).toString() == fileName;
        }

        if(exists == false)
        {
            this->mMemblockDevice.writeBlock(this->blocks++, fileName);
            didCreate = true;
        }

        return didCreate;
    }

bool createFolder(std::string folderName)
{
    bool didCreate = false;
    bool exists = false;

    fileName.resize(512);

    for(int i = 0; i < this->blocks; i++)
    {
        exists = this->mMemblockDevice.readBlock(i).toString() == fileName;
    }

    if(exists == false)
    {
        this->mMemblockDevice.writeBlock(this->blocks++, fileName);
        didCreate = true;
    }

    return didCreate;

}
void FileSystem::listDir(std::string dirList[])
{
    if(this->blocks != 0)
    {
        for(int i = 0; i < this->blocks; i++)
        {
            dirList[i] = this->mMemblockDevice.readBlock(i).toString();
        }
    }
}

int FileSystem::nrOfBlocks()
{
    return this->blocks;
}

void FileSystem::format()
{
    this->blocks = 0;
}
