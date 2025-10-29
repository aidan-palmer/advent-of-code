#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<string> grid;

bool open(int i, int j) {
    return grid[i][j] == '.';
}

void tilt_north() {
    for (size_t i = 1; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'O') {
                int curr = i;
                int next = i - 1;
                while (next >= 0 && open(next, j)) {
                    grid[curr][j] = '.';
                    grid[next][j] = 'O';
                    curr--;
                    next--;
                }
            }
        }
    }
}

void tilt_west() {
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 1; j < grid[i].size(); j++) {
            if (grid[i][j] == 'O') {
                int curr = j;
                int next = j - 1;
                while (next >= 0 && open(i, next)) {
                    grid[i][curr] = '.';
                    grid[i][next] = 'O';
                    curr--;
                    next--;
                }
            }
        }
    }
}

void tilt_south() {
    int n = grid.size();
    int m = grid[0].size();
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'O') {
                int curr = i;
                int next = i + 1;
                while (next < n && open(next, j)) {
                    grid[curr][j] = '.';
                    grid[next][j] = 'O';
                    curr++;
                    next++;
                }
            }
        }
    }
}

void tilt_east() {
    int n = grid.size();
    int m = grid[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = m - 2; j >= 0; j--) {
            if (grid[i][j] == 'O') {
                int curr = j;
                int next = j + 1;
                while (next < m && open(i, next)) {
                    grid[i][curr] = '.';
                    grid[i][next] = 'O';
                    curr++;
                    next++;
                }
            }
        }
    }
}

int load() {
    int total = 0;
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'O') {
                total += grid.size() - i;
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
    while (getline(file, line)) {
        grid.push_back(line);
    }
    vector<int> loc;
    for (int i = 0; i < 1000; i++) {
        tilt_north();
        tilt_west();
        tilt_south();
        tilt_east();
    }
    int total = load();
    cout << total << endl;
    return 0;
}