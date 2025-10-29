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

int rows(vector<string>& grid, int og) {
    for (size_t i = 0; i < grid.size() - 1; i++) {
        if (grid[i] == grid[i + 1]) {
            if (row_pattern(grid, i, i + 1) && i + 1 != og) {
                return i + 1;
            }
        }
    }
    return 0;
}

int cols(vector<string>& grid, int og) {
    for (size_t j = 0; j < grid[0].size() - 1; j++) {
        bool equal = true;
        for (size_t i = 0; i < grid.size(); i++) {
            if (grid[i][j] != grid[i][j + 1]) {
                equal = false;
                break;
            }
        }
        if (equal) {
            if (col_pattern(grid, j, j + 1) && j + 1 != og) {
                return j + 1;
            }
        }
    }
    return 0;
}

int summ(vector<string>& grid) {
    int o_r = rows(grid, -1);
    int o_c = cols(grid, -1);
    int r = 0;
    int c = 0;
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            char old = grid[i][j];
            if (grid[i][j] == '.') {
                grid[i][j] = '#';
            } else {
                grid[i][j] = '.';
            }
            r = rows(grid, o_r);
            if (r > 0 && r != o_r) {
                return 100 * r;
            } else {
                c = cols(grid, o_c);
                if (c > 0 && c != o_c) {
                    return c;
                }
            }
            r = 0;
            c = 0;
            grid[i][j] = old;
        }
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