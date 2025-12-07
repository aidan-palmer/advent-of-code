#include <bits/stdc++.h>

using namespace std;

vector<string> grid;
vector<vector<bool>> visited;
set<pair<int, int>> splits;

pair<int, int> find_s() {
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'S') {
                return make_pair(i, j);
            }
        }
    }
    return make_pair(-1, -1);
}

void init_splits(int n, int m) {
    for (int i = 0; i < n; i++) {
        vector<bool> v;
        for (int j = 0; j < m; j++) {
            v.push_back(false);
        }
        visited.push_back(v);
    }
}

void tach(int i, int j) {
    if (i >= int(grid.size()) || j < 0 || j >= int(grid[i].size())) {
        return;
    }
    if (grid[i][j] == '.') {
        if (!visited[i][j]) {
            visited[i][j] = true;
            tach(i + 1, j);
        } else {
            return;
        }
    } else {
        splits.insert(make_pair(i, j));
        tach(i, j - 1);
        tach(i, j + 1);
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
    pair<int, int> s = find_s();
    init_splits(grid.size(), grid[0].size());
    tach(s.first + 1, s.second);
    cout << splits.size() << endl;
    return 0;
}