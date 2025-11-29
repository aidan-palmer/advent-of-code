#include <bits/stdc++.h>

using namespace std;

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
    vector<int> depths;
    int total = 0;
    while (getline(file, line)) {
        depths.push_back(stoi(line));
    }
    for (size_t i = 1; i < depths.size(); i++) {
        if (depths[i] > depths[i - 1]) {
            total++;
        }
    }
    cout << total << endl;
    return 0;
}