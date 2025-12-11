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

map<string, vector<string>> devices;
int total_paths = 0;

void paths(string dev) {
    if (dev == "out") {
        total_paths++;
        return;
    }
    for (string s : devices[dev]) {
        paths(s);
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
    string token;
    while (getline(file, line)) {
        int col = index_of(line, ':');
        string key = line.substr(0, col);
        line = line.substr(col + 2);
        stringstream stream(line);
        vector<string> v;
        while (getline(stream, token, ' ')) {
            v.push_back(token);
        }
        devices[key] = v;
    }
    paths("you");
    cout << total_paths << endl;
    return 0;
}