#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <cstdint>
#include <climits>

using namespace std;

enum {
    WALL = '#',
    UP = 1,
    DOWN,
    LEFT,
    RIGHT
};

vector<ulong> scores;
size_t e_row = 1;
size_t e_col;
ulong best_path = LONG_MAX;

void find_paths(const vector<string>& grid, size_t row, size_t col, ulong score, int dir, vector<vector<bool>> visited) {
    if (grid[row][col] == WALL || visited[row][col] || score >= best_path) {
        return;
    }
    if (row == e_row && col == e_col) {
        if (score < best_path) {
            best_path = score;
        }
        return;
    }

    visited[row][col] = true;

    switch (dir) {
        case UP:
        {
            find_paths(grid, row - 1, col, score + 1, UP, visited);
            find_paths(grid, row, col + 1, score + 1001, RIGHT, visited);
            find_paths(grid, row, col - 1, score + 1001, LEFT, visited);
            break;
        }
        case DOWN:
        {
            find_paths(grid, row + 1, col, score + 1, DOWN, visited);
            find_paths(grid, row, col + 1, score + 1001, RIGHT, visited);
            find_paths(grid, row, col - 1, score + 1001, LEFT, visited);
            break;
        }
        case LEFT:
        {
            find_paths(grid, row, col - 1, score + 1, LEFT, visited);
            find_paths(grid, row - 1, col, score + 1001, UP, visited);
            find_paths(grid, row + 1, col, score + 1001, DOWN, visited);
            break; 
        }
        case RIGHT:
        {
            find_paths(grid, row, col + 1, score + 1, RIGHT, visited);
            find_paths(grid, row - 1, col, score + 1001, UP, visited);
            find_paths(grid, row + 1, col, score + 1001, DOWN, visited);
            break;   
        }
    }
    visited[row][col] = false;
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
    file.close();

    size_t s_row = grid.size() - 2;
    size_t s_col = 1;
    e_col = grid[0].size() - 2;

    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

    //best_path = (grid.size() - 3) * (grid[0].size() - 3) / 4;
    //cout << best_path << endl;

    find_paths(grid, s_row, s_col, 0, RIGHT, visited);

    cout << best_path << endl;
    return 0;
}