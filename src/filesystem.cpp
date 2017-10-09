#include "filesystem.h"

FileSystem::FileSystem() {
    this->mMemblockDevice = MemBlockDevice();
    this->blocks = 0;
}

FileSystem::~FileSystem() {

}


/* Please insert your code */
bool FileSystem::createFile(std::string fileName) {
    
        bool didCreate = false;
        bool exists = false;
    
        for(int i = 0; i < this->blocks; i++)
        {
            exists = this->mMemblockDevice.readBlock(i).toString() == fileName;
        }
    
        if(exists == false)
        {
            this->mMemblockDevice.writeBlock(this->blocks++, fileName);
            didCreate = true;
            std::cout << mMemblockDevice.size() << std::endl;
        }
        else {
            throw std::out_of_range("Already exists, change name\n");
        }
    
        return didCreate;
    }
    
bool createFolder(std::string folderName)
{
    return 0;

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
    else {
        throw std::out_of_range("Nothing to show\n");
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