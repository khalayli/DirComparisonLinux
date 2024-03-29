#include "DirectoryCmp.h"
#include "FileCmp.h"
#include "Extra.h"
#include <dirent.h>
#include <thread>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void compDirectories(const string& dirA, const string& dirB) {

    // Compare files in the directories w multithreading
    vector<string> filesdirA = listFiles(dirA);
    vector<string> filesdirB = listFiles(dirB);
    vector<thread> threads;

    for (const auto& file : filesdirA) {
        threads.push_back(thread(FileCmp::compareFiles, dirA + "/" + file, dirB + "/" + file));
    }

    for (const auto& file : filesdirB) {
        if (find(filesdirA.begin(), filesdirA.end(), file) == filesdirA.end()) {
            cout << "File " << dirB + "/" + file << " exists in " << dirB << " but not in " << dirA << "." << endl;
        }
    }

    for (auto& t : threads) {
        t.join();
    }

    // Compare subdirectories
    vector<string> dirsInDirA = listDirectories(dirA);
    vector<string> dirsInDirB = listDirectories(dirB);

    for (const auto& dir : dirsInDirA) {
        if (find(dirsInDirB.begin(), dirsInDirB.end(), dir) != dirsInDirB.end()) {
            compDirectories(dirA + "/" + dir, dirB + "/" + dir);
        }
    }

    for (const auto& dir : dirsInDirB) {
        if (find(dirsInDirA.begin(), dirsInDirA.end(), dir) == dirsInDirA.end()) {
            cout << "Directory " << dirB + "/" + dir << " exists in " << dirB << " but not in " << dirA << "." << endl;
        }
    }
}


vector<string> listFiles(const string& dir) {
    vector<string> files;
    DIR* directory;
    struct dirent* entry;

    if ((directory = opendir(dir.c_str())) != NULL) {
        while ((entry = readdir(directory)) != NULL) {
            if (entry->d_type == DT_REG) {
                files.push_back(entry->d_name);
            }
        }
        closedir(directory);
    }

    return files;
}
vector<string> listDirectories(const string& dir) {
    vector<string> dirs;
    DIR* directory;
    struct dirent* entry;

    if ((directory = opendir(dir.c_str())) != NULL) {
        while ((entry = readdir(directory)) != NULL) {
            if (entry->d_type == DT_DIR && string(entry->d_name) != "." && string(entry->d_name) != "..") {
                dirs.push_back(entry->d_name);
            }
        }
        closedir(directory);
    }

    return dirs;
}

