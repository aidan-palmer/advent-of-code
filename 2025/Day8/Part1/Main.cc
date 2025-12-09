#include <bits/stdc++.h>

using namespace std;

struct Box {
    int x, y, z;
};

vector<vector<int> > distances; // distance lookup matrix
vector<vector<bool> > visited;
vector<Box> boxes;
vector<set<int> > circuits;
vector<pair<int, int> > shortest;

int e_distance(Box p, Box q) {
    return sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2) + pow(p.z - q.z, 2));
}

void calc_distances() {
    int n = boxes.size(), i, j;
    for (i = 0; i < n; i++) {
        vector<int> row;
        vector<bool> b;
        for (j = 0; j < n; j++) {
            if (i == j) {
                row.push_back(INT32_MAX);
                b.push_back(true);
            } else {
                row.push_back(e_distance(boxes[i], boxes[j]));
                b.push_back(false);
            }
        }
        distances.push_back(row);
        visited.push_back(b);
    }
}

void short_conns(int m) {
    int i, j, k, sd, dist;
    int n = boxes.size();
    for (i = 0; i < m; i++) {
        pair<int, int> p;
        sd = INT32_MAX;
        for (j = 0; j < n - 1; j++) {
            for (k = j + 1; k < n; k++) {
                if (!visited[j][k]) {
                    dist = distances[j][k];
                    if (dist < sd) {
                        sd = dist;
                        p = make_pair(j, k);
                    }
                }
            }
        }
        shortest.push_back(p);
        visited[p.first][p.second] = true;
    }
}

void add(int x, int y) { 
    for (size_t i = 0; i < circuits.size(); i++) {
        int count = 0;
        for (int j : circuits[i]) {
            if (j == x || j == y) {
                count++;
            }
        }
        switch (count) {
            case 1:
                circuits[i].insert(x);
                circuits[i].insert(y);
                return;
            case 2:
                return;
        }
    }
    set<int> s;
    s.insert(x);
    s.insert(y);
    circuits.push_back(s);
}

bool is_connected(set<int> x, set<int> y) {
    for (int i : x) {
        for (int j : y) {
            if (i == j) {
                return true;
            }
        }
    }
    return false;
}

void merge() {
    for (size_t i = 0; i < circuits.size() - 1; i++) {
        for (size_t j = i + 1; j < circuits.size(); j++) {
            if (is_connected(circuits[i], circuits[j])) {
                for (int k : circuits[j]) {
                    circuits[i].insert(k);
                }
                circuits.erase(circuits.begin() + j);
                j--;
            }
        }
    }
}

void connect() {
    for (pair<int, int> p : shortest) {
        add(p.first, p.second);
    }
    size_t n = 0;
    while (n != circuits.size()) {
        n = circuits.size();
        merge();
    }
}

vector<int> sizes() {
    vector<int> s;
    for (set<int> i : circuits) {
        s.push_back(i.size());
    }
    sort(s.begin(), s.end(), greater<int>());
    return s;
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
    while (getline(file, line)) {
        stringstream stream(line);
        vector<int> v;
        while (getline(stream, token, ',')) {
            v.push_back(stoi(token));
        }
        Box box = {v[0], v[1], v[2]};
        boxes.push_back(box);
    }
    calc_distances();
    short_conns(1000);
    connect();
    vector<int> s = sizes();
    int total = 1;
    for (int i = 0; i < 3; i++) {
        total *= s[i];
    }
    cout << total << endl;
    return 0;
}