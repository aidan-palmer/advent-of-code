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
    int prev = 0;
    for (int i = 0; i < 3; i++) {
        prev += depths[i];
    }
    for (size_t i = 1; i < depths.size() - 2; i++) {
        int sum = 0;
        for (int j = 0; j < 3; j++) {
            sum += depths[i + j];
        }
        if (sum > prev) {
            total++;
        }
        prev = sum;
    }
    cout << total << endl;
    return 0;
}