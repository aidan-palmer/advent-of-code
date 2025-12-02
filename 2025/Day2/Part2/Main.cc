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

bool all_equal(vector<string> v) {
    for (size_t i = 0; i < v.size() - 1; i++) {
        if (v[i] != v[i + 1]) {
            return false;
        }
    }
    return true;
}

bool is_invalid(long x) {
    string s = to_string(x);
    for (size_t i = 2; i <= s.size(); i++) {
        vector<string> v;
        int n = s.size() / i;
        for (size_t j = 0; j < s.size(); j += n) {
            v.push_back(s.substr(j, n));
        }
        if (all_equal(v)) {
            return true;
        }

    }
    return false;
}

long check_ids(long start, long end) {
    long total = 0;
    for (long i = start; i <= end; i++) {
        if (is_invalid(i)) {
            total += i;
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
    string token;
    long total = 0;
    while (getline(file, line)) {
        stringstream stream(line);
        while (getline(stream, token, ',')) {
            int dash = index_of(token, '-');
            long start = stol(token.substr(0, dash));
            long end = stol(token.substr(dash + 1));
            total += check_ids(start, end);
        }
    }
    cout << total << endl;
    return 0;
}