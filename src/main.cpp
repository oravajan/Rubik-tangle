#include <iostream>
#include "Solver.h"

using namespace std;

void PrintUsage(const string & programName) {
    cout << "Usage:\n";
    cout << programName << " " << "inputFile.txt" << endl;
}

int main(int argc, char * argv[]) {
    if(argc<=1) {
        cerr << "Missing argument!\n\n";
        PrintUsage(argv[0]);
        return 1;
    }
    Solver solver;
    solver.Solve(argv[1], cout);
    return 0;
}
