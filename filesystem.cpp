
#include"filesystem.h"
#include <iostream>

FileSystem::FileSystem() {
	this->mMemblockDevice = MemBlockDevice();
	this->blocks = 0;
	this->currentFolder = 0;
	this->nrOfFolders = 0;
	this->folderCap = 2;

	this->fso = new Folder *[this->nrOfFolders];
	for (int i = 0; i < this->nrOfFolders; i++)
	{
		this->fso[i] = nullptr;
	}

	this->fso[this->currentFolder] = new Folder(0, 0, "/");

}

FileSystem::~FileSystem() {
	for (int i = 0; i < this->nrOfFolders; i++)
	{
		delete this->fso[i];
	}
	delete[] this->fso;
}


/* Please insert your code */
bool FileSystem::createFile(std::string fileName)
{
	bool didCreate = false;
	bool exists = false;

	fileName = this->fso[this->currentFolder]->getName() + fileName;
	fileName.resize(512);

	for (int i = 0; i < this->blocks; i++)
	{
		if (this->mMemblockDevice.readBlock(i).toString() == fileName)
			exists = true;
	}

	if (exists == false)
	{
		this->mMemblockDevice.writeBlock(this->blocks, fileName);
		File * tempFile = new File(fileName, this->blocks++);
		this->fso[this->currentFolder]->addFile(tempFile);
		didCreate = true;
	}
	return didCreate;
}

bool FileSystem::createFolder(std::string folderName)
{
	bool didCreate = false;
	bool exists = false;

	folderName = this->fso[this->currentFolder]->getName() + folderName + "/";

	for (int i = 0; i < this->nrOfFolders; i++)
	{
		if (this->fso[i]->getName() == folderName)
		{
			exists = true;
		}
	}

	if (!exists)
	{
		if (this->nrOfFolders == this->folderCap)
		{
			this->expandFolderSystem();
		}
		Folder * tempNew = new Folder(this->currentFolder, this->nrOfFolders, folderName);

		this->fso[this->nrOfFolders] = tempNew;
		this->fso[this->currentFolder]->addFolder(tempNew);
		this->nrOfFolders++;
		didCreate = true;
	}

	return didCreate;

}

bool FileSystem::goToFolder(std::string nextFolder)
{
	bool couldEnter = false;
	nextFolder = this->fso[this->currentFolder]->getName() + nextFolder;

	if (this->fso[this->currentFolder]->searchItem(nextFolder))
	{
		int toFolder = findFolder(nextFolder);
		if (toFolder != -1)
		{
			this->currentFolder = toFolder;
			couldEnter = true;
			std::cout << "uppdaterade " << this->currentFolder << std::endl;
		}
	}
	return couldEnter;
}

void FileSystem::listDir(std::string dirList[])
{
	if (this->fso[this->currentFolder]->getFolderSize() != 0)
	{
		FileSystemObject ** temp = new FileSystemObject *[this->fso[this->currentFolder]->getFolderSize()];

		this->fso[this->currentFolder]->getFolderStructure(temp);
		std::string objectName = "";
		int stringLength = 0;

		for (int i = 0; i < this->fso[this->currentFolder]->getFolderSize(); i++)
		{
			stringLength = this->fso[this->currentFolder]->getName().length();
			objectName = temp[i]->getName().substr(stringLength);
			dirList[i] = objectName;
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

int FileSystem::findFolder(std::string name) const
{
	int posOfFolder = -1;
	for (int i = 0; i < this->nrOfFolders; i++)
	{
		if (this->fso[i]->getName() == name)
		{
			posOfFolder = i;
		}
	}
	return posOfFolder;
}

std::string FileSystem::getCurrentFolderName() const
{
	return this->fso[this->currentFolder]->getName();
}

int FileSystem::getFolderSize() const
{
	return this->fso[this->currentFolder]->getFolderSize();
}

void FileSystem::expandFolderSystem()
{
	this->folderCap = this->folderCap + 5;
	Folder ** temp = new Folder*[this->folderCap];
	for (int i = 0; i < this->nrOfFolders; i++)
	{
		temp[i] = this->fso[i];
	}
	for (int i = 0; i < this->nrOfFolders; i++)
	{
		delete this->fso[i];
	}
	// Kan inte deleta arrayen, den verkar ta bort b�da ist�llet f�r en.

	delete [] this->fso;
	this->fso = temp;
}