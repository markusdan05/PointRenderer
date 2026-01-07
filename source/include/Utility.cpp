#include "Utility.h"

#include <iostream>
#include <fstream>

std::string ParseFile(const std::string& filePath) {
    std::fstream fileStream(filePath, std::ios_base::in);
    if (!fileStream.is_open()) {
        std::cout << "Failed to open shader file <" << filePath << ">!" << std::endl;
        return "";
    }

    fileStream.seekg(0, std::ios::end);
    int fileLength = fileStream.tellg();
    fileStream.seekg(0, std::ios::beg);

    std::string parsedFile(fileLength, '\0');
    fileStream.read(&parsedFile[0], fileLength);

    return parsedFile;
}