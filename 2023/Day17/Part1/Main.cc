#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/**
 * Heuristics: 
 * Always choose the node with the smallest value
 * Only go right or down
 */

vector<string> grid;
int n, m;

int ctoi(char c) {
    return c - '0';
}

// dir: 0: right, 1: down
int path(int i, int j, int dir, int len) {
    if (i == n - 1 && j == m - 1) {
        return ctoi(grid[i][j]);
    }
    if (len < 3) {
        int right = 10;
        int down = 10;
        if (j + 1 < m) {
            right = ctoi(grid[i][j + 1]);
        }
        if (i + 1 < n) {
            down = ctoi(grid[i + 1][j]);
        }
        if (right < down) {
            if (dir == 0) {
                len++;
            } else {
                dir = 0;
                len = 1;
            }
            return path(i, j + 1, dir, len) + ctoi(grid[i][j]);
        } else {
            if (dir == 1) {
                len++;
            } else {
                dir = 1;
                len = 1;
            }
            return path(i + 1, j, dir, len) + ctoi(grid[i][j]);
        }
    } else {
        if (dir == 0) {
            dir = 1;
            len = 1;
            return path(i + 1, j, dir, len) + ctoi(grid[i][j]);
        } else {
            dir = 0;
            len = 1;
            return path(i, j + 1, dir, len) + ctoi(grid[i][j]);
        }
    }
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
    n = grid.size();
    m = grid[0].size();
    cout << path(0, 0, 0, 1) << endl;
    return 0;
}