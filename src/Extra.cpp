#include "Extra.h"
#include <iostream>
#include <fstream>

using namespace std;

namespace Extra {

void displayHelp() {
    cout << "DirectoryComparison Tool Usage:" << endl;
    cout << "./dir_compare <directory1> <directory2>" << endl;
    cout << "Compares the contents of two directories." << endl;
    
}

void formatOutput(const string& message) {
    
    cout << "=== " << message << " ===" << endl;
}

void logError(const string& errorMessage) {
    ofstream logFile("error_log.txt", ios::app);  // Err logging
    if (logFile.is_open()) {
        logFile << errorMessage << endl;
        logFile.close();
    } else {
        cerr << "Unable to open error log file." << endl;
    }
}

} 
