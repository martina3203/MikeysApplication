#include "settings.h"

settings::settings()
{

}

void settings::test()
{
    if (readFile("settings.txt") == true)
    {
        std::cout << "File read" << std::endl;
    }
    std::vector<std::string> fileNamesReturned = returnFileLocations();
    for (unsigned int i = 0; i < fileNamesReturned.size(); i++)
    {
        std::cout << fileNamesReturned.at(i) << std::endl;
    }
}

bool settings::readFile(std::string fileName)
{
    std::ifstream inputFile;
    inputFile.open(fileName.c_str());
    if (inputFile.is_open())
    {
        std::string file;
        while(inputFile.eof() != true)
        {
            std::getline(inputFile,file);
            fileNames.push_back(file);
        }
        inputFile.close();
        return true;
    }
    else
    {
        inputFile.close();
        return false;
    }
}

bool settings::writeFile(std::string fileName)
{
    std::ofstream outputFile;
    //Default file list
    if (fileName == "")
    {
        outputFile.open("settings.txt");
    }
    else
    {
        std::string customFileName = fileName + ".txt";
        outputFile.open(customFileName.c_str());
    }
    if (outputFile.is_open())
    {
        for (unsigned int i = 0; i < fileNames.size(); i++)
        {
            outputFile << fileNames.at(i) << std::endl;
        }
        outputFile.close();
        return true;
    }
    else
    {
        outputFile.close();
        return false;
    }
}

void settings::addFileLocation(std::string newLocation)
{
    fileNames.push_back(newLocation);
}

void settings::removeFileLocation(std::string oldFileLocation)
{
    for (unsigned int i = 0; i < fileNames.size(); i++)
    {
        if (fileNames.at(i) == oldFileLocation)
        {
            for (unsigned int j = i; j < (fileNames.size()-1); j++)
            {
                fileNames.at(j) = fileNames.at(j+1);
            }
            fileNames.pop_back();
        }
    }
}

std::vector<std::string> settings::returnFileLocations()
{
    return fileNames;
}

settings::~settings()
{

}
