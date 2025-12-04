#include <bits/stdc++.h>

using namespace std;

vector<string> grid;

bool can_access(int x, int y) {
    int adj = 0;
    int n = grid.size();
    int m = grid[0].size();
    if (x - 1 >= 0) {
        // Up
        if (grid[x - 1][y] == '@') {
            adj++;
        }
        // Up left
        if (y - 1 >= 0 && grid[x - 1][y - 1] == '@') {
            adj++;
        }
        // Up right
        if (y + 1 < m && grid[x - 1][y + 1] == '@') {
            adj++;
        }
    }
    if (x + 1 < n) {
        // Down
        if (grid[x + 1][y] == '@') {
            adj++;
        }
        // Down left
        if (y - 1 >= 0 && grid[x + 1][y - 1] == '@') {
            adj++;
        }
        // Down right
        if (y + 1 < m && grid[x + 1][y + 1] == '@') {
            adj++;
        }
    }
    // Left
    if (y - 1 >= 0 && grid[x][y - 1] == '@') {
        adj++;
    }
    // Right
    if (y + 1 < m && grid[x][y + 1] == '@') {
        adj++;
    }
    return adj < 4;
}

void rm_rolls(vector<pair<int, int>>& r) {
    for (pair<int, int> p : r) {
        grid[p.first][p.second] = '.';
    }
}

int count_rolls() {
    int total = 0;
    vector<pair<int, int>> r;
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '@') {
                if (can_access(i, j)) {
                    r.push_back(make_pair(i, j));
                    total++;
                }
            }
        }
    }
    if (total > 0) {
        rm_rolls(r);
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
    int total = 0;
    while (true) {
        int count = count_rolls();
        if (count == 0) {
            break;
        }
        total += count;
    }
    cout << total << endl;
    return 0;
}