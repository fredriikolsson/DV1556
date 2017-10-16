#include <iostream>
#include <sstream>
#include "filesystem.h"

const int MAXCOMMANDS = 8;
const int NUMAVAILABLECOMMANDS = 15;

std::string availableCommands[NUMAVAILABLECOMMANDS] = {
    "quit","format","ls","create","cat","createImage","restoreImage",
    "rm","cp","append","mv","mkdir","cd","pwd","help"
};

/* Takes usercommand from input and returns number of commands, commands are stored in strArr[] */
int parseCommandString(const std::string &userCommand, std::string strArr[]);
int findCommand(std::string &command);
bool quit();
std::string help();

/* More functions ... */
void expand(std::string* dirList, int &listSize);
void listDirectory(FileSystem fs);
void createFile(FileSystem & fs, std::string commandArr);

int main(void) {
    FileSystem fs;
    
	std::string userCommand, commandArr[MAXCOMMANDS];
	std::string user = "user@DV1492";    // Change this if you want another user to be displayed
    //std::string currentDir = "/";    // current directory, used for output
    std::string currentDir = fs.getCurrentFolderName();
    bool bRun = true;


    do {
        std::cout << user << ":" << currentDir << "$ ";
        getline(std::cin, userCommand);

        int nrOfCommands = parseCommandString(userCommand, commandArr);
        if (nrOfCommands > 0) {

            int cIndex = findCommand(commandArr[0]);
            switch(cIndex) {

			case 0: //quit
				bRun = quit();
                break;
            case 1: // format
            fs.format();
                break;
            case 2: // ls
                listDirectory(fs);
                break;
            case 3: // create
                createFile(fs, commandArr[1]);
                //fs.createFile(commandArr[1]);
                break;
            case 4: // cat
                break;
            case 5: // createImage
                break;
            case 6: // restoreImage
                break;
            case 7: // rm
                break;
            case 8: // cp
                break;
            case 9: // append
                break;
            case 10: // mv
                break;
            case 11: // mkdir
                break;
            case 12: // cd
                break;
            case 13: // pwd
                break;
            case 14: // help
                std::cout << help() << std::endl;
                break;
            default:
                std::cout << "Unknown command: " << commandArr[0] << std::endl;
            }
        }
    } while (bRun == true);

    return 0;
}

int parseCommandString(const std::string &userCommand, std::string strArr[]) {
    std::stringstream ssin(userCommand);
    int counter = 0;
    while (ssin.good() && counter < MAXCOMMANDS) {
        ssin >> strArr[counter];
        counter++;
    }
    if (strArr[0] == "") {
        counter = 0;
    }
    return counter;
}
int findCommand(std::string &command) {
    int index = -1;
    for (int i = 0; i < NUMAVAILABLECOMMANDS && index == -1; ++i) {
        if (command == availableCommands[i]) {
            index = i;
        }
    }
    return index;
}

bool quit() {
	std::cout << "Exiting\n";
	return false;
}

std::string help() {
    std::string helpStr;
    helpStr += "OSD Disk Tool .oO Help Screen Oo.\n";
    helpStr += "-----------------------------------------------------------------------------------\n" ;
    helpStr += "* quit:                             Quit OSD Disk Tool\n";
    helpStr += "* format;                           Formats disk\n";
    helpStr += "* ls     <path>:                    Lists contents of <path>.\n";
    helpStr += "* create <path>:                    Creates a file and stores contents in <path>\n";
    helpStr += "* cat    <path>:                    Dumps contents of <file>.\n";
    helpStr += "* createImage  <real-file>:         Saves disk to <real-file>\n";
    helpStr += "* restoreImage <real-file>:         Reads <real-file> onto disk\n";
    helpStr += "* rm     <file>:                    Removes <file>\n";
    helpStr += "* cp     <source> <destination>:    Copy <source> to <destination>\n";
    helpStr += "* append <source> <destination>:    Appends contents of <source> to <destination>\n";
    helpStr += "* mv     <old-file> <new-file>:     Renames <old-file> to <new-file>\n";
    helpStr += "* mkdir  <directory>:               Creates a new directory called <directory>\n";
    helpStr += "* cd     <directory>:               Changes current working directory to <directory>\n";
    helpStr += "* pwd:                              Get current working directory\n";
    helpStr += "* help:                             Prints this help screen\n";
    return helpStr;
}

/* Insert code for your shell functions and call them from the switch-case */
void expand(std::string* dirList, int &listSize)
{
    listSize = listSize + 10;
    std::string* temp = new std::string [listSize];
    for(int i = 0;i<listSize-10;i++)
    {
        temp[i] = dirList[i];
    }

    delete [] dirList;
    dirList = temp;
}
void listDirectory(FileSystem fs)
{
    int listSize = 10;
    std::string * dirList = new std::string[listSize];

    if(fs.nrOfBlocks() > listSize){
        expand(dirList, listSize);
    }

    if(fs.nrOfBlocks() > 0)
    {
        std::cout << "Listing directory" << std::endl;
        fs.listDir(dirList);

        for(int i = 0; i < fs.nrOfBlocks(); i++)
        {
            std::cout << dirList[i] << std::endl;
        }
    }
    else
    {
        std::cout << "Empty Repository " << std::endl;
    }

}

void createFile(FileSystem & fs, std::string commandArr)
{
    bool createResult = fs.createFile(commandArr);
    if(!createResult)
    {
        std::cout << "File already exists with that name. Use another name.\n";
    }
}
