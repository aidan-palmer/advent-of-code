#include <fstream>
#include <iostream>
#include <sstream>
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
    string token;

    while (getline(file, line)) {
        stringstream stream(line);

        while (getline(stream, token, ' ')) {

        }
    }

//    cout << total << endl;
    return 0;
}
