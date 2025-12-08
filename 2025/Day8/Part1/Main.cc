#include <bits/stdc++.h>

using namespace std;

struct Box {
    int x, y, z;
};

vector<vector<int>> distances; // distance lookup matrix
vector<vector<bool>> visited;
vector<Box> boxes;
vector<set<int>> circuits;
vector<pair<int, int>> shortest;

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
            cout << j << " ";
        }
        cout << endl << x << " " << y << " " << count << endl << endl;
        
        switch (count) {
            case 1:
                circuits[i].insert(x);
                circuits[i].insert(y);
                return;
            case 2:
                return;
        }
    }
    set<int> s = {x, y};
    circuits.push_back(s);
}

void merge() {

}

void connect() {
    for (pair<int, int> p : shortest) {
        add(p.first, p.second);
    }
    merge();
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
    short_conns(10);
    connect();
    vector<int> s = sizes();
    /*
    for (int i : s) {
        cout << i << endl;
    }*/
   /*
    for (set<int> se : circuits) {
        for (int i : se) {
            cout << i << " ";
        }
        cout << endl;
    }*/
    int total = 1;
    for (int i = 0; i < 3; i++) {
        total *= s[i];
    }
    /*
    for (pair<int, int> p : shortest) {
        cout << p.first << " " << p.second << endl;
    }*/

    cout << total << endl;
    return 0;
}