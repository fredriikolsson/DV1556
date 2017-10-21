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
public:
	Folder(int previousFolder, int folderPos, std::string name);
	virtual ~Folder();
	// Folder(Folder & anotherFolder);    
	Folder* Folder::clone() const;

	bool addFile(File * toAdd);
	bool addFolder(Folder * toAdd);

	bool searchItem(std::string name) const;
	//kunna lägga till mappar och filer.
	//detta ska vara kopplat i FILESYSTEM_H

	void getFolderStructure(FileSystemObject ** array);

	int getPos() const; // getFolderPos;
	int getPrevousFolder() const;
	int getFolderSize() const;
	// std::string getName() const;

	void operator=(Folder & anotherFolder);
	void expandFolder();
};

#endif // FILES_H
