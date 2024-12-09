#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

enum {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};

vector<int> start(const vector<string>& grid) {
    size_t i, j;
    vector<int> pos;

    for (i = 0; i < grid.size(); i++) {
        for (j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '^') {
                pos.push_back(UP);
                pos.push_back(i);
                pos.push_back(j);
                return pos;
            } else if (grid[i][j] == 'v') {
                pos.push_back(DOWN);
                pos.push_back(i);
                pos.push_back(j);
                return pos;
            } else if (grid[i][j] == '<') {
                pos.push_back(LEFT);
                pos.push_back(i);
                pos.push_back(j);
                return pos;
            } else if (grid[i][j] == '>') {
                pos.push_back(RIGHT);
                pos.push_back(i);
                pos.push_back(j);
                return pos;
            }
        }
    }
    return pos;
}

bool contains(const vector<vector<int>>& indices, int& x, int& y) {
    for (size_t i = 0; i < indices.size(); i++) {
        if (indices[i][0] == x && indices[i][1] == y) {
            return true;
        }
    }
    return false;
}

long visit(const vector<string>& grid, int& dir, int& x, int& y) {
    long total = 0;
    vector<vector<int>> indices;
    
    while (x >= 0 && x < grid.size() && y >= 0 && y < grid[x].size()) {
        while (grid[x][y] != '#') {
            switch (dir) {
                case UP:
                    x--;
                    break;
                case DOWN:
                    x++;
                    break;
                case LEFT:
                    y--;
                    break;
                case RIGHT:
                    y++;
                    break;
            }
            if (x < 0 || x >= grid.size() || y < 0 || y >= grid[x].size()) {
                return total;
            }
            if (!contains(indices, x, y) && grid[x][y] != '#') {
                vector<int> z;
                z.push_back(x);
                z.push_back(y);
                indices.push_back(z);
                total++;
            }
        }
        switch (dir) {
            case UP:
                x++;
                dir = RIGHT;
                break;
            case DOWN:
                x--;
                dir = LEFT;
                break;
            case LEFT:
                y++;
                dir = UP;
                break;
            case RIGHT:
                y--;
                dir = DOWN;
                break;
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
    vector<string> grid;

    while (getline(file, line)) {
        grid.push_back(line);
    }

    vector<int> pos = start(grid);
    cout << visit(grid, pos[0], pos[1], pos[2]) << endl;
    return 0;
}
