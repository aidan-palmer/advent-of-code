#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>
#include <map>

using namespace std;

map<size_t, vector<size_t>> nines;

bool contains(size_t i, size_t j) {
    for (size_t k = 0; k < nines[i].size(); k++) {
        if (nines[i][k] == j) {
            return true;
        }
    }
    return false;
}

size_t path(vector<vector<int>>& grid, size_t i, size_t j, int prev) {
    if (i >= grid.size() || j >= grid[0].size() || prev + 1 != grid[i][j]) {
        return 0;
    }
    if (grid[i][j] == 9) {
        if (contains(i, j)) {
            return 0;
        } else {
            nines[i].push_back(j);
            return 1;
        }
    }
    return path(grid, i + 1, j, grid[i][j]) + path(grid, i - 1, j, grid[i][j]) + 
        path(grid, i, j + 1, grid[i][j]) + path(grid, i, j - 1, grid[i][j]);
}

size_t score(vector<vector<int>>& grid) {
    size_t total = 0, i, j;

    for (i = 0; i < grid.size(); i++) {
        for (j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 0) {
                size_t p = path(grid, i, j, -1);
                total += p;
                nines.clear();
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
    vector<vector<int>> grid;

    while (getline(file, line)) {
        vector<int> nums;

        for (size_t i = 0; i < line.size(); i++) {
            nums.push_back(line[i] - '0');
        }
        grid.push_back(nums);
    }

    cout << score(grid) << endl;
    return 0;
}
