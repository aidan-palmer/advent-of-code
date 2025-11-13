#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

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
    int cycle = 0;
    int total = 0;
    while (getline(file, line)) {
        if (line.substr(0, 4) == "addx") {
            int val = stoi(line.substr(5));
            for (int i = 0; i < 2; i++) {
                cycle++;
                if (cycle == 20 || cycle == 60 || cycle == 100 || 
                    cycle == 140 || cycle == 180 || cycle == 220) {
                        total += cycle * X;
                }
            }
            X += val;
        } else {
            cycle++;
            if (cycle == 20 || cycle == 60 || cycle == 100 || 
                cycle == 140 || cycle == 180 || cycle == 220) {
                    total += cycle * X;
            }
        }
    }
    cout << total << endl;
    return 0;
}