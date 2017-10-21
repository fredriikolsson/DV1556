#include"Folder.h"
#include<iostream>

Folder::Folder(int previousFolder, int folderPos, std::string name)
	:FileSystemObject(name)
{
	this->previousFolder = previousFolder;
	this->folderPos = folderPos;

	this->currentItemsInFolder = 0;
	this->folderSize = 10;
	this->structure = new FileSystemObject *[this->folderSize];
	for (int i = 0; i<this->folderSize; i++)
	{
		this->structure[i] = nullptr;
	}

}

Folder::~Folder() {
	for (int i = 0; i < this->currentItemsInFolder; i++)
	{
		delete this->structure[i];
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

	if (!searchItem(toAdd->getName()))
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

	if (!searchItem(toAdd->getName()))
	{
		this->structure[this->currentItemsInFolder] = toAdd;
		this->currentItemsInFolder = this->currentItemsInFolder + 1;
		canAddFolder = true;
	}
	return canAddFolder;
}

bool Folder::searchItem(std::string name) const
{
	bool isFound = false;
	std::cout << "items in folder " << this->currentItemsInFolder << std::endl;
	for (int i = 0; i < this->currentItemsInFolder; i++)
	{
		if (this->structure[i]->getName() == name)
			isFound = true;
	}


	return isFound;
}

void Folder::getFolderStructure(FileSystemObject ** array)
{
	std::cout << "printar från folder" << std::endl;
	for (int i = 0; i < this->getFolderSize(); i++)
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

	delete[] this->structure;
	this->structure = temp;
}

void Folder::operator=(Folder & anotherFolder) 
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