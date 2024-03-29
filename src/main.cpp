#include "DirectoryCmp.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: "  << argv[0] << " <directory1> <directory2>" << endl;
        return 1;
    }

    string dirA = argv[1];
    string dirB = argv[2];

    compDirectories(dirA, dirB);

    return 0;

}
