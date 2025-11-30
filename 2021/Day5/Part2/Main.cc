#include <bits/stdc++.h>

using namespace std;

int index_of(string s, char c) {
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            return i;
        }
    }
    return -1;
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
    vector<pair<int, int>> p1;
    vector<pair<int, int>> p2;
    while (getline(file, line)) {
        int dash = index_of(line, '-');
        string s1 = line.substr(0, dash - 1);
        string s2 = line.substr(dash + 3);
        stringstream stream1(s1);
        stringstream stream2(s2);
        pair<int, int> point1, point2;
        vector<int> tmp;
        while (getline(stream1, token, ',')) {
            tmp.push_back(stoi(token));
        }
        point1 = make_pair(tmp[0], tmp[1]);
        tmp.clear();
        while (getline(stream2, token, ',')) {
            tmp.push_back(stoi(token));
        }
        point2 = make_pair(tmp[0], tmp[1]);
        p1.push_back(point1);
        p2.push_back(point2);
    }
    map<pair<int, int>, int> points;
    int j, k;
    // same x = vertical, same y = horizontal
    for (size_t i = 0; i < p1.size(); i++) {
        if (p1[i].first == p2[i].first) {
            if (p1[i].second < p2[i].second) { // increasing
                for (j = p1[i].second; j <= p2[i].second; j++) {
                    points[{p1[i].first, j}]++;
                }
            } else {
                for (j = p2[i].second; j <= p1[i].second; j++) {
                    points[{p1[i].first, j}]++;
                }
            }
        } else if (p1[i].second == p2[i].second) {
            if (p1[i].first < p2[i].first) {
                for (j = p1[i].first; j <= p2[i].first; j++) {
                    points[{j, p1[i].second}]++;
                }
            } else {
                for (j = p2[i].first; j <= p1[i].first; j++) {
                    points[{j, p1[i].second}]++;
                }
            }
        } else {
            int diffx = abs(p1[i].first - p2[i].first);
            int diffy = abs(p1[i].second - p2[i].second);
            if (diffx == diffy) {
                int x1 = p1[i].first;
                int y1 = p1[i].second;
                int x2 = p2[i].first;
                int y2 = p2[i].second;
                if (x1 > x2) {
                    x1 = x2;
                    y1 = y2;
                    x2 = p1[i].first;
                    y2 = p1[i].second;
                }
                if (y1 < y2) {
                    for (j = x1, k = y1; j <= x2; j++, k++) {
                        points[{j, k}]++;
                    }
                } else {
                    for (j = x1, k = y1; j <= x2; j++, k--) {
                        points[{j, k}]++;
                    }
                }
            }
        }
    }
    int sum = 0;
    for (const auto& p : points) {
        if (p.second > 1) {
            sum++;
        }
    }
    cout << sum << endl;
    return 0;
}