#include <bits/stdc++.h>

using namespace std;


bool is_possible(vector<int>& sides) {
    sort(sides.begin(), sides.end());
    return sides[0] + sides[1] > sides[2];
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
    int num_possible = 0;

    while (getline(file, line)) {
        stringstream stream(line);
        vector<int> sides;

        while (getline(stream, token, ' ')) {
            if (!token.empty()) {
                sides.push_back(stoi(token));
            }
        }
        if (is_possible(sides)) {
            num_possible++;
        }
    }
    cout << num_possible << endl;
    return 0;
}