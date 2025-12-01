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
    int prev = dial;
    while (getline(file, line)) {
        char dir = line[0];
        int dist = stoi(line.substr(1));
        if (dir == 'L') {
            if (dist >= prev) {
                zeros += 1 + (dist - prev) / 100;
            }
            dial = (prev - dist % 100 + 100) % 100;
        } else {
            int first = (100 - prev) % 100;
            if (first == 0) {
                first = 100;
            }
            if (dist >= first) {
                zeros += 1 + (dist - first) / 100;
            }
            dial = (prev + dist % 100) % 100;
        }
        if (dial == 0) {
            zeros++;
        }
        prev = dial;
    }
    cout << zeros << endl;
    return 0;
}