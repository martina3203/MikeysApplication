#ifndef SETTINGS_H
#define SETTINGS_H

/*
 * Settings class contains the file information needed to load previous profiles and
 * other saved settings needed by the application
*/


#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ostream>

class settings
{
public:
    settings();
    void test();
    void addFileLocation(std::string);
    void removeFileLocation(std::string);
    std::vector<std::string> returnFileLocations();
    bool readFile(std::string);
    bool writeFile(std::string fileName = "");

    ~settings();
private:
    std::vector<std::string> fileNames;
};

#endif // SETTINGS_H
