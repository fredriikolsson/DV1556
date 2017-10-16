#ifndef FOLDER_H
#define FOLDER_H

#include "FileSystemObject.h"
#include "File.h"
#include <string>

class Folder : public FileSystemObject
{
private:
    int previousFolder;
    std::string folderName;
    int folderPos;

    int folderSize;
    int currentItemsInFolder;
    FileSystemObject ** structure;
public:
    Folder(int previousFolder, int folderPos, std::string folderName);
    virtual ~Folder();
    Folder(Folder & anotherFolder);    

    bool addFile(File * toAdd);
    bool addFolder(Folder * toAdd);
    //kunna lägga till mappar och filer.
    //detta ska vara kopplat i FILESYSTEM_H

    void getFolderStructure(FileSystemObject ** array);

    int getPos() const; // getFolderPos;
    int getPrevousFolder() const;
    int getFolderSize() const;
    std::string getFolderName() const;

    void expandFolder();
};

#endif // FILES_H
