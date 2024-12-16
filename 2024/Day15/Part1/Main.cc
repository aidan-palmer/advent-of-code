#include <fstream>
#include <iostream>
#include <vector>
#include <array>

using namespace std;

enum {
    LEFT = '<',
    RIGHT = '>',
    UP = '^',
    DOWN = 'v'
};

array<size_t, 2> robot_index(const vector<string>& grid) {
    array<size_t, 2> index;
    size_t i, j;

    for (i = 0; i < grid.size(); i++) {
        for (j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '@') {
                index = {i, j};
                return index;
            }
        }
    }
    return index;
}

bool has_space(const vector<string>& grid, char dir, size_t i, size_t j) {
    size_t k;

    switch (dir) {
        case LEFT:
        {
            for (k = j - 1; k > 0; k--) {
                if (grid[i][k] == '#') {
                    return false;
                } else if (grid[i][k] == '.') {
                    return true;
                }
            }
            return false;
        }
        case RIGHT:
        {
            for (k = j + 1; k < grid[i].size() - 1; k++) {
                if (grid[i][k] == '#') {
                    return false;
                } else if (grid[i][k] == '.') {
                    return true;
                }
            }
            return false;
        }
        case UP:
        {
            for (k = i - 1; k > 0; k--) {
                if (grid[k][j] == '#') {
                    return false;
                } else if (grid[k][j] == '.') {
                    return true;
                }
            }
            return false;
        }
        case DOWN:
        {
            for (k = i + 1; k < grid.size() - 1; k++) {
                if (grid[k][j] == '#') {
                    return false;
                } else if (grid[k][j] == '.') {
                    return true;
                }      
            }
            return false;
        }
    }
    return 0;
}

void shift(vector<string>& grid, char dir, size_t i, size_t j) {
    size_t k, l;

    switch (dir) {
        case LEFT:
        {
            for (k = j - 1; k > 0; k--) {
                if (grid[i][k] == '.') {
                    for (l = k; l < j; l++) {
                        grid[i][l] = 'O';
                    }
                    return;
                }
            }
            break;
        }
        case RIGHT:
        {
            for (k = j + 1; k < grid[i].size() - 1; k++) {
                if (grid[i][k] == '.') {
                    for (l = k; l > j; l--) {
                        grid[i][l] = 'O';
                    }
                    return;
                }
            }
            break;
        }
        case UP:
        {
            for (k = i - 1; k > 0; k--) {
                if (grid[k][j] == '.') {
                    for (l = k; l < i; l++) {
                        grid[l][j] = 'O';
                    }
                    return;
                }
            }         
            break;
        }
        case DOWN:
        {
            for (k = i + 1; k < grid.size() - 1; k++) {
                if (grid[k][j] == '.') {
                    for (l = k; l > i; l--) {
                        grid[l][j] = 'O';
                    }
                    return;
                }
            }         
            break;
        }
    }
}

void move(vector<string>& grid, char dir, size_t& y, size_t& x) {
    size_t i(y);
    size_t j(x);

    switch (dir) {
        case LEFT:
            j--;
            break;
        case RIGHT:
            j++;
            break;
        case UP:
            i--;
            break;
        case DOWN:
            i++;
            break;
    }
    
    if (grid[i][j] == '#') {
        return;
    } else if (grid[i][j] == '.') {
        grid[i][j] = '@';
        grid[y][x] = '.';
        y = i;
        x = j;
    } else {
        if (has_space(grid, dir, i, j)) {
            shift(grid, dir, i, j);
            grid[i][j] = '@';
            grid[y][x] = '.';
            y = i;
            x = j;
        }
    }
}

long coordinates(const vector<string>& grid) {
    long total = 0;
    size_t i, j;

    for (i = 1; i < grid.size() - 1; i++) {
        for (j = 1; j < grid[i].size() - 1; j++) {
            if (grid[i][j] == 'O') {
                total += 100 * i + j;
            }
        }
    }
    return total;
}

// for debugging
void print(const vector<string>& grid) {
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
    cout << endl;
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
    string moves;
    bool is_grid = true;
    size_t i;

    while (getline(file, line)) {
        if (line.empty()) {
            is_grid = false;
            continue;
        }
        if (is_grid) {
            grid.push_back(line);
        } else {
            moves += line;
        }
    }
    file.close();
    array<size_t, 2> location = robot_index(grid);

    for (i = 0; i < moves.size(); i++) { 
        move(grid, moves[i], location[0], location[1]);
    }

    cout << coordinates(grid) << endl;
    return 0;
}