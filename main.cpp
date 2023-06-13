// do not mind my bad code, i am still kinda a beginner.

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

void modifyRBXLfile(const std::string& filename) {
    std::ifstream inputFile(filename, std::ios::binary | std::ios::ate);
    std::ofstream outputFile("modified_" + filename, std::ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return;
    }

    const std::string targetStr = "WrapTarget";
    const char* replacementVal = "\x00";
    std::streampos fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);
    std::string fileData((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    size_t pos = 0;
    while ((pos = fileData.find(targetStr, pos)) != std::string::npos) {
        std::memcpy(&fileData[pos], replacementVal, strlen(replacementVal));
        pos += strlen(replacementVal);
    }

    outputFile.write(fileData.data(), fileSize);
    inputFile.close();
    outputFile.close();
}

int main() {
    std::string filename;
    std::cout << "Enter the name of the file to modify (with extension): ";
    std::getline(std::cin, filename);
    modifyRBXLfile(filename);

    return 0;
}
