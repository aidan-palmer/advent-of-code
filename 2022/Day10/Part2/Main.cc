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
    int X = 1;
    char screen[6][40];
    int row = 0;
    int col = 0;
    while (getline(file, line)) {
        if (line.substr(0, 4) == "addx") {
            int val = stoi(line.substr(5));
            for (int i = 0; i < 2; i++) {
                if (col >= X - 1 && col <= X + 1) {
                    screen[row][col] = '#';
                } else {
                    screen[row][col] = '.';
                }
                col++;
                if (col > 39) {
                    row++;
                    col = 0;
                }
            }
            X += val;
        } else {
            if (col >= X - 1 && col <= X + 1) {
                screen[row][col] = '#';
            } else {
                screen[row][col] = '.';
            }
            col++;
            if (col > 39) {
                row++;
                col = 0;
            }
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 40; j++) {
            cout << screen[i][j];
        }
        cout << endl;
    }
    return 0;
}