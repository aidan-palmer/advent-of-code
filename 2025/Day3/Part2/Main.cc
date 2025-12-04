#include <bits/stdc++.h>

using namespace std;

int ctoi(char c) {
    return c - '0';
}

long max_jolt(string s) {
    string jolt;
    size_t i = 0, j;
    int max, max_idx, x;
    size_t skipped = 0;
    while (skipped < s.size() - 12 && jolt.size() != 12) {
        max = -1;
        max_idx = -1;
        for (j = i; j < i + (s.size() - 12) - skipped + 1; j++) {
            x = ctoi(s[j]);
            if (x > max) {
                max = x;
                max_idx = j;
            }
        }
        skipped += max_idx - i;
        i = max_idx + 1;
        jolt.push_back(s[max_idx]);
    }
    if (jolt.size() < 12) {
        jolt += s.substr(i, 12 - jolt.size());
    }
    return stol(jolt);
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
    long total = 0;
    while (getline(file, line)) {
        total += max_jolt(line);
    }
    cout << total << endl;
    return 0;
}