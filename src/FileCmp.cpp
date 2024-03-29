#include "FileCmp.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>

namespace FileCmp {

    bool getFileSize(const std::string& filePath, off_t& size) {
        struct stat fileInfo;
        if (::stat(filePath.c_str(), &fileInfo) != 0) {
            std::cerr << "Error fetching size for file: " << filePath << std::endl;
            return false;
        }
        size = fileInfo.st_size;
        return true;
    }

    bool getFileMetadata(const std::string& filePath, struct stat& fileInfo) {
        if (::stat(filePath.c_str(), &fileInfo) != 0) {
            std::cerr << "Error fetching metadata for file: " << filePath << std::endl;
            return false;
        }
        return true;
    }

    void compareFiles(const std::string& filePathA, const std::string& filePathB) {
        off_t sizeA, sizeB;

        if (!getFileSize(filePathA, sizeA) || !getFileSize(filePathB, sizeB)) {
            return;
        }

        if (sizeA != sizeB) {
            std::cout << "Files " << filePathA << " and " << filePathB << " have different sizes." << std::endl;
            return;
        }

        struct stat metadataA, metadataB;
        if (getFileMetadata(filePathA, metadataA) && getFileMetadata(filePathB, metadataB)) {
            if (metadataA.st_mtime != metadataB.st_mtime) {
                std::cout << "Files " << filePathA << " and " << filePathB << " have different modification times." << std::endl;
            }
            if ((metadataA.st_mode & 07777) != (metadataB.st_mode & 07777)) {
                std::cout << "Files " << filePathA << " and " << filePathB << " have different permissions." << std::endl;
            }
            // here u can add more comparisons 
        }

        // File content cmprison
        std::ifstream fileA(filePathA, std::ios::binary);
        std::ifstream fileB(filePathB, std::ios::binary);

        if (!fileA.is_open() || !fileB.is_open()) {
            std::cerr << "Error opening one of the files: " << filePathA << " or " << filePathB << std::endl;
            return;
        }

        char charA, charB;
        while (fileA.get(charA) && fileB.get(charB)) {
            if (charA != charB) {
                std::cout << "Files " << filePathA << " and " << filePathB << " differ in content." << std::endl;
                return;
            }
        }

        if (!fileA.eof() || !fileB.eof()) {
            std::cout << "Files " << filePathA << " and " << filePathB << " have different content lengths." << std::endl;
        } else {
            std::cout << "Files " << filePathA << " and " << filePathB << " are identical." << std::endl;
        }
    }

    // Any new functions can be addedd here
}

