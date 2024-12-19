#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>
#include <cstdint>
#include <climits>

using namespace std;

#define SIZE 71
#define NUM_BYTES 1024

enum {
    X = 0,
    Y
};

enum {
    BYTE = '#',
    UP = 1,
    DOWN,
    LEFT,
    RIGHT
};

const size_t e_row = SIZE - 1;
const size_t e_col = SIZE - 1;
int best_path = INT32_MAX;

void find_paths(array<array<char, SIZE>, SIZE> grid, size_t row, size_t col, int steps, vector<vector<bool>> visited) {
    if (row >= SIZE || col >= SIZE || grid[row][col] == BYTE || visited[row][col] || steps >= best_path) {
        return;
    }
    if (row == e_row && col == e_col) {
        if (steps < best_path) {
            best_path = steps;
        }
        return;
    }

    visited[row][col] = true;

    find_paths(grid, row, col + 1, steps + 1, visited); // right
    find_paths(grid, row + 1, col, steps + 1, visited); // down
    find_paths(grid, row, col - 1, steps + 1, visited); // left 
    find_paths(grid, row - 1, col, steps + 1, visited); // up


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
    string token;
    vector<vector<int>> indices;
    array<array<char, SIZE>, SIZE> grid;
    size_t i;

    while (getline(file, line)) {
        stringstream stream(line);
        vector<int> index;

        while (getline(stream, token, ',')) {
            index.push_back(stoi(token));
        }
        indices.push_back(index);
    }
    file.close();

    for (i = 0; i < SIZE; i++) {
        grid[i].fill('.');
    }

    for (i = 0; i < NUM_BYTES; i++) {
        grid[indices[i][Y]][indices[i][X]] = BYTE;
    }
/*
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
*/

    vector<vector<bool>> visited(SIZE, vector<bool>(SIZE, false));

    find_paths(grid, 0, 0, 0, visited);

    cout << best_path << endl;
    return 0;
}