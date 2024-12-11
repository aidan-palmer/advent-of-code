#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Incorrect usage\n";
        return 1;
    }
    fstream file(argv[1]);

    if (!file) {
        cerr << "Error: file not found.\n";
        return 2;
    }
    string line;
    vector<string> grid;

    while (getline(file, line)) {
        grid.push_back(line);
    }

    //cout <<  << endl;
    return 0;
}
