#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<vector<string>> grids;

bool row_pattern(vector<string>& grid, int a, int b) {
    int n = grid.size();
    a--;
    b++;
    while (a >= 0 && b < n) {
        if (grid[a] != grid[b]) {
            return false;
        }
        a--;
        b++;
    }
    return true;
}

bool col_pattern(vector<string>& grid, int a, int b) {
    int n = grid[0].size();
    a--;
    b++;
    while (a >= 0 && b < n) {
        for (size_t i = 0; i < grid.size(); i++) {
            if (grid[i][a] != grid[i][b]) {
                return false;
            }
        }
        a--;
        b++;
    }
    return true;
}

int rows(vector<string>& grid) {
    for (size_t i = 0; i < grid.size() - 1; i++) {
        if (grid[i] == grid[i + 1]) {
            if (row_pattern(grid, i, i + 1)) {
                return i + 1;
            }
        }
    }
    return 0;
}

int cols(vector<string>& grid) {
    for (size_t j = 0; j < grid[0].size() - 1; j++) {
        bool equal = true;
        for (size_t i = 0; i < grid.size(); i++) {
            if (grid[i][j] != grid[i][j + 1]) {
                equal = false;
                break;
            }
        }
        if (equal) {
            if (col_pattern(grid, j, j + 1)) {
                return j + 1;
            }
        }
    }
    return 0;
}

int summ(vector<string>& grid) {
    int r = rows(grid);
    int c = 0;
    if (r == 0) {
        c = cols(grid);
    }
    return 100 * r + c;
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
    vector<string> tmp;
    while (getline(file, line)) {
        if (line.empty()) {
            grids.push_back(tmp);
            tmp.clear();
            continue;
        }
        tmp.push_back(line);
    }
    grids.push_back(tmp);
    int total = 0;
    for (vector<string> s : grids) {
        total += summ(s);
    }
    cout << total << endl;
    return 0;
}