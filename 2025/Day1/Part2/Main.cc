#include <iostream>
#include <fstream>

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
        int count = 0;
        if (dir == 'L') {
            dial -= dist;
            while (dial < 0) {
                dial += 100;
                count++;
            }
            if (dial == 0 && prev == 0) {
                count--;
            }
            if (prev == 0 && dist % 100 < 100) {
                count--;
            }
        } else {
            dial += dist;
            while (dial > 99) {
                dial -= 100;
                count++;
            }
            if (dial == 0 && count > 0) {
                count--;
            }
        }
        zeros += count;
        if (dial == 0) {
            zeros++;
        }
        prev = dial;
    }
    cout << zeros << endl;
    return 0;
}