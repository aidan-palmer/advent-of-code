#include <bits/stdc++.h>

using namespace std;

size_t area(pair<long, long>& p, pair<long, long>& q) {
    return (abs(p.first - q.first) + 1) * (abs(p.second - q.second) + 1);
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
    vector<pair<long, long>> tiles;
    while (getline(file, line)) {
        stringstream stream(line);
        vector<long> v;
        while (getline(stream, token, ',')) {
            v.push_back(stol(token));
        }
        tiles.push_back(make_pair(v[0], v[1]));
    }
    size_t max = 0;
    for (size_t i = 0; i < tiles.size() - 1; i++) {
        for (size_t j = i + 1; j < tiles.size(); j++) {
            size_t a = area(tiles[i], tiles[j]);
            if (a > max) {
                max = a;
            }
        }
    }
    cout << max << endl;
    return 0;
}