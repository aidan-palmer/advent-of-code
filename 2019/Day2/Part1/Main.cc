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
    vector<int> intcode;
    //int total = 0;

    while (getline(file, line)) {
        stringstream stream(line);

        while (getline(stream, token, ',')) {
            intcode.push_back(stoi(token));
        }
    }
    intcode[1] = 12;
    intcode[2] = 2;

    for (size_t i = 0; i < intcode.size(); i += 4) {
        switch (intcode[i]) {
            case 1:
            {
                intcode[intcode[i + 3]] = intcode[intcode[i + 1]] + intcode[intcode[i + 2]];
                break;
            }
            case 2:
            {
                intcode[intcode[i + 3]] = intcode[intcode[i + 1]] * intcode[intcode[i + 2]];
                break;              
            }
            case 99:
            {
                cout << intcode[0] << endl;
                return 0;
            }
        }
    }

    cout << intcode[0] << endl;
    return 0;
}