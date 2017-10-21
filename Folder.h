#ifndef FOLDER_H
#define FOLDER_H

#include "FileSystemObject.h"
#include "File.h"
#include <string>

class Folder : public FileSystemObject
{
private:
	int previousFolder;
	int folderPos;

	int folderSize;
	int currentItemsInFolder;
	FileSystemObject ** structure;
	
	void deAllocateMemory();
public:
	Folder(int previousFolder, int folderPos, std::string name);
	virtual ~Folder();
	// Folder(Folder & anotherFolder);    
	Folder* Folder::clone() const;

	bool addFile(File * toAdd);
	bool addFolder(Folder * toAdd);

	int removeFile(int posToRemove);

	int searchItem(std::string name) const;
	//kunna lägga till mappar och filer.
	//detta ska vara kopplat i FILESYSTEM_H

	void getFolderStructure(FileSystemObject ** array);

	int getPos() const; // getFolderPos;
	int getFolderPos(int pos);
	int getPrevousFolder() const;
	int getFolderSize() const;
	std::string getFileContent(int posOfFile) const;
	// std::string getName() const;

	// void operator=(Folder & anotherFolder);
	void expandFolder();
	bool isFile(int posToCheck);
};

#endif // FILES_H
