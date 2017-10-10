#ifndef FOLDER_H
#define FOLDER_H

#include "FilesSystemObject.h"

class Folder : public FilesSystemObject
{
private:
    int previousFolder;
    int folderPos;
    FilesSystemObject ** structures;
public:
    Folder(int previousFolder, int folderPos);
    ~Folder();

    //kunna lägga till mappar och filer.
    //detta ska vara kopplat i FILESYSTEM_H

    int getFolderPos();
    int getPrevousFolder();
};

#endif // FILES_H

#endif
