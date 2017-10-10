#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include<string>
#include "memblockdevice.h"
#include "FilesSystemObject.h"
#include "Folder.h"

class FileSystem
{
private:
    MemBlockDevice mMemblockDevice;
    // Here you can add your own data structures
    int blocks;
    int ** folders;

    Folder * fso; //Initiera
public:
    FileSystem();
    ~FileSystem();

    /* These API functions need to be implemented
	   You are free to specify parameter lists and return values
    */

    /* This function creates a file in the filesystem */
     bool createFile(std::string fileName);

    /* Creates a folder in the filesystem */
     bool createFolder(std::string folderName);

    /* Removes a file in the filesystem */
    // removeFile(...);

    /* Removes a folder in the filesystem */
    // removeFolder(...);

    /* Function will move the current location to a specified location in the filesystem */
    // goToFolder(...);

    /* This function will get all the files and folders in the specified folder */
     void listDir(std::string dirList[]);

    /* Add your own member-functions if needed */

    /* Number Of Blocks*/
    int nrOfBlocks();

    /* Format */
    void format();

};

#endif // FILESYSTEM_H
