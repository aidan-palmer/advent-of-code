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
    string token;
    vector<int> state;
    while (getline(file, line)) {
        stringstream stream(line);
        while (getline(stream, token, ',')) {
            state.push_back(stoi(token));
        }
    }
    size_t i, j;
    int k;
    for (i = 0; i < 80; i++) {
        int eights = 0;
        for (j = 0; j < state.size(); j++) {
            state[j]--;
            if (state[j] == -1) {
                state[j] = 6;
                eights++;
            }
        }
        for (k = 0; k < eights; k++) {
            state.push_back(8);
        }
    }
    cout << state.size() << endl;
    return 0;
}