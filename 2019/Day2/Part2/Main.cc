#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int fuel(int mass) {
    return mass / 3 - 2;
}

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
    vector<int> modules;
    int total = 0;

    while (getline(file, line)) {
        modules.push_back(stoi(line));
    }

    for (int mass : modules) {
        int tmp = fuel(mass);

        while (tmp > 0) {
            total += tmp;
            tmp = fuel(tmp);
        }
    }

    cout << total << endl;
    return 0;
}