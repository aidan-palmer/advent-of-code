#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

struct Vertex {
    char tile;
    int i;
    int j;
};

struct Edge {
    Vertex v1;
    Vertex v2;
};

map<pair<int, int>, pair<Edge, Edge>> edges;
vector<string> grid;

int loop(int i, int j, int prev_i, int prev_j) {
    int count = 0;
    while (grid[i][j] != 'S') {
        if (grid[i][j] == '.') {
            return 0;
        }
        Edge e1 = edges[make_pair(i, j)].first;
        Edge e2 = edges[make_pair(i, j)].second;
        int es[4][2] = {{e1.v1.i, e1.v1.j}, {e1.v2.i, e1.v2.j}, {e2.v1.i, e2.v1.j}, {e2.v2.i, e2.v2.j}};
        bool has_curr = false;
        for (int x = 0; x < 4; x++) {
            //cout << "FOR" << endl;
            cout << "Edge: " << es[x][0] << " " << es[x][1] << endl;
            cout << "Current: " << i << " " << j << endl;

            if ((es[x][0] != prev_i && es[x][1] != prev_j)) {
                cout << "IF" << endl;
                i = es[x][0];
                j = es[x][1];
                prev_i = i;
                prev_j = j;
                count++;
                break;
            }
        }
    }
    return count;
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
    int n = grid.size();
    int m = grid[0].size();
    pair<int, int> start;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            //cout << i << " " << j << endl;
            //cout << n << " " << m << endl;
            if (grid[i][j] != '.') {
                Vertex v, v1, v2;
                v.tile = grid[i][j];
                if (v.tile == '|' && i - 1 >= 0 && i + 1 < n) {
                    v1 = {grid[i - 1][j], i - 1, j};
                    v2 = {grid[i + 1][j], i + 1, j};
                } else if (v.tile == '-' && j - 1 >= 0 && j + 1 < m) {
                    v1 = {grid[i][j - 1], i, j - 1};
                    v2 = {grid[i][j + 1], i, j + 1};
                } else if (v.tile == 'L' && i - 1 >= 0 && j + 1 < m) {
                    v1 = {grid[i - 1][j], i - 1, j};
                    v2 = {grid[i][j + 1], i, j + 1};
                } else if (v.tile == 'J' && i - 1 >= 0 && j - 1 >= 0) {
                    v1 = {grid[i][j - 1], i, j - 1};
                    v2 = {grid[i - 1][j], i - 1, j};
                } else if (v.tile == '7' && i + 1 < n && j - 1 >= 0) {
                    v1 = {grid[i + 1][j], i + 1, j};
                    v2 = {grid[i][j - 1], i, j - 1};
                } else if (v.tile == 'F' && i + 1 < n && j + 1 < m) {
                    v1 = {grid[i + 1][j], i + 1, j};
                    v2 = {grid[i][j + 1], i, j + 1};
                } else if (v.tile == 'S') {
                    start = make_pair(i, j);
                }
                Edge e1 = {v1, v};
                Edge e2 = {v2, v};
                edges[make_pair(i, j)] = make_pair(e1, e2);
            }
        }
    }
    vector<int> counts;
    if (start.first - 1 >= 0) {
        counts.push_back(loop(start.first - 1, start.second, start.first, start.second));
    }
    if (start.second - 1 >= 0) {
        counts.push_back(loop(start.first, start.second - 1, start.first, start.second));
    }
    if (start.first + 1 < n) {
        counts.push_back(loop(start.first + 1, start.second, start.first, start.second));
    }
    if (start.second + 1 < m) {
        counts.push_back(loop(start.first, start.second + 1, start.first, start.second));
    }
    for (int i : counts) {
        cout << i << endl;
    }
    return 0;
}