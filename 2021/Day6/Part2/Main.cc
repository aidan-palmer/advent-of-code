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
    int i, j;
    map<int, unsigned long long int> fish;
    for (int s : state) {
        fish[s]++;
    }
    for (i = 0; i < 256; i++) {
        for (j = 0; j <= 8; j++) {
            fish[j - 1] = fish[j];
        }
        fish[8] = fish[-1];
        fish[6] += fish[-1];
    }
    unsigned long long int count = 0;
    for (i = 0; i <= 8; i++) {
        count += fish[i];
    }
    cout << count << endl;
    return 0;
}