#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>
#include <cstdint>
#include <climits>

using namespace std;

#define SIZE 7 // change to 71
#define NUM_BYTES 12 // change to 1024

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

    //cout << shortest_path(grid) << endl;
    return 0;
}