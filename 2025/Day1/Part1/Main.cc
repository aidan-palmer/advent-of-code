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
    int dial = 50;
    int zeros = 0;
    while (getline(file, line)) {
        char dir = line[0];
        int dist = stoi(line.substr(1));
        if (dir == 'L') {
            dial -= dist;
        } else {
            dial += dist;
        }
        while (dial < 0) {
            dial += 100;
        }
        while (dial > 99) {
            dial -= 100;
        }
        if (dial == 0) {
            zeros++;
        }
    }
    cout << zeros << endl;
    return 0;
}