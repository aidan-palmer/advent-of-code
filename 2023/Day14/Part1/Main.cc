#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<string> grid;

bool open(int i, int j) {
    return grid[i][j] == '.';
}

void tilt() {
    for (size_t i = 1; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'O') {
                int curr = i;
                int next = i - 1;
                while (next >= 0 && open(next, j)) {
                    grid[curr][j] = '.';
                    grid[next][j] = 'O';
                    curr--;
                    next--;
                }
            }
        }
    }
}

int load() {
    int total = 0;
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'O') {
                total += grid.size() - i;
            }
        }
    }
    return total;
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
    while (getline(file, line)) {
        grid.push_back(line);
    }
    tilt();
    int total = load();
    cout << total << endl;
    return 0;
}