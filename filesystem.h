#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include "memblockdevice.h"
#include "FileSystemObject.h"
#include "Folder.h"
#include "File.h"

class FileSystem
{
private:
	MemBlockDevice mMemblockDevice;
	// Here you can add your own data structures
	int blocks;

	Folder ** fso; //Initiera
	int currentFolder;
	int nrOfFolders;
	int folderCap;
public:
	FileSystem();
	virtual ~FileSystem();

	/* These API functions need to be implemented
	You are free to specify parameter lists and return values
	*/

	/* This function creates a file in the filesystem */
	bool createFile(std::string fileName, std::string content = "Empty");

	std::string cat(std::string fileName) const;

	/* Creates a folder in the filesystem */
	bool createFolder(std::string folderName);

	/* Removes a file in the filesystem */
	// removeFile(...);
	bool removeFile(std::string name);
	bool removeFolder(std::string name, int posOfFolderToEnter = -1);
	bool removeItem(std::string name);

	/* Removes a folder in the filesystem */
	// removeFolder(...);

	/* Function will move the current location to a specified location in the filesystem */
	// goToFolder(...);
	bool goToFolder(std::string nextFolder);

	/* This function will get all the files and folders in the specified folder */
	void listDir(std::string dirList[]);

	/* Add your own member-functions if needed */

	/* Number Of Blocks*/
	int nrOfBlocks();

	/* Format */
	void format();

	void createImage();

	int findFolder(std::string name) const;
	std::string getCurrentFolderName() const;
	int getFolderSize() const;
	int getCurrentFolder() const;
	void expandFolderSystem();

};

#endif // FILESYSTEM_H
