#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<string> grid;
map<tuple<int, int, int>, bool> visited;
set<pair<int, int>> energized;

// Directions: 0: up, 1: down, 2: right, 3: left
void path(int i, int j, int dir) {
    if (i >= int(grid.size()) || i < 0 ||
        j >= int(grid[0].size()) || j < 0) {
            return;
    }
    if (visited[{i, j, dir}]) {
        return;
    }
    visited[{i, j, dir}] = true;
    energized.insert({i, j});
    if (grid[i][j] == '.') {
        switch (dir) {
            case 0:
                path(i - 1, j, dir);
                break;
            case 1:
                path(i + 1, j, dir);
                break;
            case 2:
                path(i, j + 1, dir);
                break;
            case 3:
                path(i, j - 1, dir);
                break;
        }
    } else if (grid[i][j] == '/') {
        switch (dir) {
            case 0:
                path(i, j + 1, 2);
                break;
            case 1:
                path(i, j - 1, 3);
                break;
            case 2:
                path(i - 1, j, 0);
                break;
            case 3:
                path(i + 1, j, 1);
                break;
        }
    } else if (grid[i][j] == '\\') {
        switch (dir) {
            case 0:
                path(i, j - 1, 3);
                break;
            case 1:
                path(i, j + 1, 2);
                break;
            case 2:
                path(i + 1, j, 1);
                break;
            case 3:
                path(i - 1, j, 0);
                break;
        }
    } else if (grid[i][j] == '|') {
        switch (dir) {
            case 0:
                path(i - 1, j, 0);
                break;
            case 1:
                path(i + 1, j, 1);
                break;
            default:
                path(i - 1, j, 0);
                path(i + 1, j, 1);
                break;
        }
    } else if (grid[i][j] == '-') {
        switch (dir) {
            case 2:
                path(i, j + 1, 2);
                break;
            case 3:
                path(i, j - 1, 3);
                break;
            default:
                path(i, j - 1, 3);
                path(i, j + 1, 2);
                break;
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
    size_t max_energized = 0;
    int n = grid.size();
    int m = grid[0].size();
    for (int i = 0; i < m; i++) {
        path(0, i, 1);
        if (energized.size() > max_energized) {
            max_energized = energized.size();
        }
        energized.clear();
        visited.clear();
        path(n - 1, i, 0);
        if (energized.size() > max_energized) {
            max_energized = energized.size();
        }
        energized.clear();
        visited.clear();
        if (i == 0) {
            path(0, 0, 2);
            if (energized.size() > max_energized) {
                max_energized = energized.size();
            }
            energized.clear();
            visited.clear();
            path(n - 1, 0, 2);
            if (energized.size() > max_energized) {
                max_energized = energized.size();
            }
            energized.clear();    
            visited.clear();        
        } else if (i == m - 1) {
            path(0, i, 3);
            if (energized.size() > max_energized) {
                max_energized = energized.size();
            }
            energized.clear();     
            visited.clear();      
            path(n - 1, i, 3);
            if (energized.size() > max_energized) {
                max_energized = energized.size();
            }
            energized.clear();        
            visited.clear();     
        }
    }
    for (int i = 1; i < n - 1; i++) {
        path(i, 0, 2);
        if (energized.size() > max_energized) {
            max_energized = energized.size();
        }
        energized.clear();
        visited.clear();
        path(i, m - 1, 3);
        if (energized.size() > max_energized) {
            max_energized = energized.size();
        }
        energized.clear();
        visited.clear();
    }
    cout << max_energized << endl;
    return 0;
}