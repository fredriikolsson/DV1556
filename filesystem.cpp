
#include"filesystem.h"
#include <iostream>

FileSystem::FileSystem() {
	this->mMemblockDevice = MemBlockDevice();
	this->blocks = 0;
	this->currentFolder = 0;
	this->nrOfFolders = 0;
	this->folderCap = 2;

	this->fso = new Folder *[this->folderCap];
	for (int i = 0; i < this->folderCap; i++)
	{
		this->fso[i] = nullptr;
	}

	this->nrOfFolders++;

	this->fso[this->currentFolder] = new Folder(0, 0, "~/");

}

FileSystem::~FileSystem() 
{
	this->removeFolder("~/", 0);
	delete[] this->fso;
}


/* Please insert your code */
bool FileSystem::createFile(std::string fileName, std::string content)
{
	bool didCreate = false;
	bool exists = false;

	fileName = this->fso[this->currentFolder]->getName() + fileName;

	// Har tempFileName för att jämföra och lägga till i buffern, medans i filsystemet heter det utan resizen för att inte få 
	// extremt långa ls
	std::string tempFileName = fileName;
	tempFileName.resize(512);

	for (int i = 0; i < this->blocks; i++)
	{
		if (this->mMemblockDevice.readBlock(i).toString() == tempFileName)
			exists = true;
	}

	if (exists == false)
	{
		this->mMemblockDevice.writeBlock(this->blocks, tempFileName);
		File * tempFile = new File(fileName, content, this->blocks++);
		this->fso[this->currentFolder]->addFile(tempFile);
		didCreate = true;
	}
	return didCreate;
}

std::string FileSystem::cat(std::string fileName) const
{
	std::string defaultText = "No file by that name";

	std::string theFileName = this->fso[this->currentFolder]->getName() + fileName;

	int posOfFile = this->fso[this->currentFolder]->searchItem(theFileName);
	if (posOfFile != -1)
	{
		defaultText = this->fso[this->currentFolder]->getFileContent(posOfFile);
	}

	return defaultText;
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
bool FileSystem::removeItem(std::string name)
{
	bool didRemove = false;
	std::string theName = this->fso[this->currentFolder]->getName() + name;
	int posToCheck = this->fso[this->currentFolder]->searchItem(theName);
	if (posToCheck != -1)
	{
		bool isFile = this->fso[this->currentFolder]->isFile(posToCheck);
		if (isFile)
		{
			didRemove = this->removeFile(theName);
		}
		else
		{
			theName = this->fso[this->currentFolder]->getName() + name + "/";
			didRemove = this->removeFolder(theName);
		}
	}
	theName = this->fso[this->currentFolder]->getName() + name + "/";
	posToCheck = this->fso[this->currentFolder]->searchItem(theName);
	if (posToCheck != -1)
	{
		theName = this->fso[this->currentFolder]->getName() + name + "/";
		didRemove = this->removeFolder(theName);
	}
	return didRemove;
}
bool FileSystem::removeFile(std::string name)
{
	bool didRemove = false;
	int posToRemove = this->fso[this->currentFolder]->searchItem(name);
	if (posToRemove != -1)
	{
		int removeFromBufferPos = this->fso[this->currentFolder]->removeFile(posToRemove);
		for (int i = removeFromBufferPos; i < this->blocks - 1; i++)
		{
			this->mMemblockDevice.writeBlock(i, this->mMemblockDevice.readBlock(i + 1).toString());
		}
		this->blocks--;
		didRemove = true;
	}

	return didRemove;
}

bool FileSystem::removeFolder(std::string name, int posOfFolderToEnter)
{
	//Default värde 
	if (posOfFolderToEnter == -1)
	{
		posOfFolderToEnter = this->currentFolder;
	}

	posOfFolderToEnter = findFolder(name);

	bool didRemove = false;

	int posToRemove = this->fso[posOfFolderToEnter]->searchItem(name);

	if (posToRemove != -1)
	{
		for (int i = 0; i < this->fso[posOfFolderToEnter]->getFolderSize(); i++)
		{
			// Kolla om det är en fil
			if (this->fso[posOfFolderToEnter]->isFile(i))
			{
				this->fso[posOfFolderToEnter]->removeFile(i);
			}
			// ta bort mappen och rensa allt i mappen
			else 
			{
				this->removeFolder(this->fso[posOfFolderToEnter]->getName(), this->fso[posOfFolderToEnter]->getFolderPos(i));
			
			}
		}
		delete [] this->fso[posOfFolderToEnter];
		didRemove = true;

		//Sortera
		for (int i = posOfFolderToEnter; i < this->nrOfFolders - 1; i++)
		{
			this->fso[i] = this->fso[i + 1];
			std::cout << "VARDE " + std::to_string(i) << std::endl;
		}
		
	}

	return didRemove;
}

bool FileSystem::goToFolder(std::string nextFolder)
{
	bool couldEnter = false;
	if (nextFolder == "..") {
		this->currentFolder = this->fso[this->currentFolder]->getPrevousFolder();
		couldEnter = true;
	}
	else {
		nextFolder = this->fso[this->currentFolder]->getName() + nextFolder;

		if (this->fso[this->currentFolder]->searchItem(nextFolder) != -1)
		{
			int toFolder = findFolder(nextFolder);
			if (toFolder != -1)
			{
				this->currentFolder = toFolder;
				couldEnter = true;
			}
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

void FileSystem::createImage()
{

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

int FileSystem::getCurrentFolder() const
{
	return this->currentFolder;
}

void FileSystem::expandFolderSystem()
{
	this->folderCap = this->folderCap + 5;
	Folder ** temp = new Folder*[this->folderCap];
	for (int i = 0; i < this->nrOfFolders; i++)
	{
		temp[i] = this->fso[i];
		//temp nr i får fso nr i, på fso nr i ligger ett mappsystem, 
	}

	// Kan inte deletea arrayen, den verkar ta bort båda istället för en.
	delete this->fso;
	this->fso = temp;
}
