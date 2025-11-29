#include <bits/stdc++.h>

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
    int horiz = 0;
    int depth = 0;
    int x;
    while (getline(file, line)) {
        string pre = line.substr(0, 2);
        if (pre == "fo") {
            x = stoi(line.substr(8));
            horiz += x;
        } else if (pre == "do") {
            x = stoi(line.substr(5));
            depth += x;
        } else {
            x = stoi(line.substr(3));
            depth -= x;
        }
    }
    cout << horiz * depth << endl;
    return 0;
}