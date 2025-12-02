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

bool is_invalid(long x) {
    string s = to_string(x);
    string a = s.substr(0, s.size() / 2);
    string b = s.substr(s.size() / 2);
    return a == b;
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