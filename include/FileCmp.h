#pragma once

#include <string>
#include <sys/types.h>  // for off_t
#include <sys/stat.h>   // for struct stat

namespace FileCmp {
    bool getFileSize(const std::string& filePath, off_t& size);
    void compareFiles(const std::string& filePathA, const std::string& filePathB);
    bool getFileMetadata(const std::string& filePath, struct stat& fileInfo);
}

