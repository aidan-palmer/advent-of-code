#include <bits/stdc++.h>

using namespace std;

int max_jolt(string s) {
    size_t i, j;
    string a;
    int num;
    int max = -1;
    for (i = 0; i < s.size() - 1; i++) {
        for (j = i + 1; j < s.size(); j++) {
            a = {s[i], s[j]};
            num = stoi(a);
            if (num > max) {
                max = num;
            }
        }
    }
    return max;
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
    int total = 0;
    while (getline(file, line)) {
        total += max_jolt(line);
    }
    cout << total << endl;
    return 0;
}