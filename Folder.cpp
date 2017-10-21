#include"Folder.h"
#include<iostream>

Folder::Folder(int previousFolder, int folderPos, std::string name)
	:FileSystemObject(name)
{
	this->previousFolder = previousFolder;
	this->folderPos = folderPos;

	this->currentItemsInFolder = 0;
	this->folderSize = 1;
	this->structure = new FileSystemObject *[this->folderSize];
	for (int i = 0; i<this->folderSize; i++)
	{
		this->structure[i] = nullptr;
	}

}

Folder::~Folder() {
	//this->deAllocateMemory();
}

void Folder::deAllocateMemory()
{
	for (int i = 0; i < this->currentItemsInFolder; i++)
	{
		File * isFile = dynamic_cast<File*>(this->structure[i]);
		if (isFile != nullptr)
		{
			delete this->structure[i];
		}
	}
	delete[] this->structure;
}

// Folder::Folder(Folder & anotherFolder)
// {
//     this->previousFolder = anotherFolder.previousFolder;
//     this->folderPos = anotherFolder.folderPos;


//     this->currentItemsInFolder = anotherFolder.currentItemsInFolder;
//     this->folderSize = anotherFolder.folderSize;

//     for(int i = 0; i < this->currentItemsInFolder; i++)
//     {
//         this->structure[i] = anotherFolder.structure[i];
//     }
// }

Folder* Folder::clone() const
{
	return new Folder(*this);
}

bool Folder::addFile(File * toAdd)
{
	bool canAddFile = false;
	if (this->currentItemsInFolder == this->folderSize)
		this->expandFolder();

	if (searchItem(toAdd->getName()) == -1)
	{
		this->structure[this->currentItemsInFolder] = toAdd;
		this->currentItemsInFolder = this->currentItemsInFolder + 1;
		canAddFile = true;
	}


	return canAddFile;
}

bool Folder::addFolder(Folder * toAdd)
{
	bool canAddFolder = false;
	if (this->currentItemsInFolder == this->folderSize)
		this->expandFolder();

	if (-1 == searchItem(toAdd->getName()))
	{
		this->structure[this->currentItemsInFolder] = toAdd;
		this->currentItemsInFolder = this->currentItemsInFolder + 1;
		canAddFolder = true;
	}
	return canAddFolder;
}

int Folder::removeFile(int posToRemove)
{
	int didRemove = -1;
	File * isFile = dynamic_cast<File*>(this->structure[posToRemove]);
	if (isFile != nullptr)
	{
		didRemove = isFile->getPos();
		delete this->structure[posToRemove];
		for (int i = posToRemove; i < this->currentItemsInFolder - 1; i++)
		{
			this->structure[i] = this->structure[i + 1];
		}
		this->currentItemsInFolder--;
	}
	return didRemove;
}

int Folder::searchItem(std::string name) const
{
	int isFound = -1;
	for (int i = 0; i < this->currentItemsInFolder; i++)
	{
		if (this->structure[i]->getName() == name)
			isFound = i;
	}

	return isFound;
}

void Folder::getFolderStructure(FileSystemObject ** array)
{
	for (int i = 0; i < this->getFolderSize(); i++)
	{
		array[i] = this->structure[i];
	}
}

int Folder::getPos() const
{
	return this->folderPos;
}

int Folder::getFolderPos(int pos)
{
	Folder * isFolder = dynamic_cast<Folder*>(this->structure[pos]);
	return isFolder->getPos();
}

int Folder::getPrevousFolder() const
{
	return this->previousFolder;
}

int Folder::getFolderSize() const
{
	return this->currentItemsInFolder;
}

std::string Folder::getFileContent(int posOfFile) const
{
	std::string fileContent = "";
	File * isFile = dynamic_cast<File*>(this->structure[posOfFile]);
	if (isFile != nullptr)
	{
		fileContent = isFile->getContent();
	}
	return fileContent;
}

 //std::string Folder::getName () const
 //{
 //    return this->name;
 //}

void Folder::expandFolder()
{
	this->folderSize = this->folderSize + 10;
	FileSystemObject ** temp = new FileSystemObject *[this->folderSize];

	for (int i = 0; i < this->currentItemsInFolder; i++)
	{
		temp[i] = this->structure[i];
	}
	for (int i = this->currentItemsInFolder; i < this->folderSize; i++)
	{
		temp[i] = nullptr;
	}

	delete this->structure;
	this->structure = temp;
}

bool Folder::isFile(int posToCheck)
{
	File * isFile = dynamic_cast<File*>(this->structure[posToCheck]);
	return isFile != nullptr;
}

//void Folder::operator=(Folder & anotherFolder) 
// {
//	setName(anotherFolder.getName());
//	this->deAllocateMemory();
//
//     this->previousFolder = anotherFolder.previousFolder;
//     this->folderPos = anotherFolder.folderPos;
//     this->currentItemsInFolder = anotherFolder.currentItemsInFolder;
//     this->folderSize = anotherFolder.folderSize;
//
//	 this->structure = new FileSystemObject*[anotherFolder.folderSize];
//
//     for(int i = 0; i < this->currentItemsInFolder; i++)
//     {
//         this->structure[i] = anotherFolder.structure[i];
//     }
// }