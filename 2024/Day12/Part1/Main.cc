#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>
#include <map>
#include <set>

using namespace std;

map<size_t, set<size_t>> visited;

bool contains(size_t i, size_t j) {
    if (visited.count(i) == 0) {
        return false;
    }
    for (auto& v : visited[i]) {
        if (v == j) {
            return true;
        }
    }
    return false;
}

size_t area = 0;
size_t perimiter = 0;

void region(vector<string>& grid, size_t i, size_t j, char type) {
    if (contains(i, j)) {
        if (grid[i][j] != type) {
            perimiter++;
        }
        return;
    }
    if (i >= grid.size() || j >= grid[0].size() || grid[i][j] != type) {
        perimiter++;
        return;
    }
    if (grid[i][j] == type) {
        visited[i].insert(j);
        area++;
    }
    region(grid, i + 1, j, type);
    region(grid, i - 1, j, type);
    region(grid, i, j + 1, type);
    region(grid, i, j - 1, type);
}

size_t price(vector<string>& grid) {
    size_t total = 0, i, j;
    vector<size_t> perimiters;
    vector<size_t> areas;

    for (i = 0; i < grid.size(); i++) {
        for (j = 0; j < grid[i].size(); j++) {
            if (!contains(i, j)) {
                region(grid, i, j, grid[i][j]);
                areas.push_back(area);
                perimiters.push_back(perimiter);
                area = 0;
                perimiter = 0;
            }
        }
    }
    for (i = 0; i < areas.size(); i++) {
        total += areas[i] * perimiters[i];
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
    vector<string> grid;

    while (getline(file, line)) {
        grid.push_back(line);
    }

    cout << price(grid) << endl;
    return 0;
}
