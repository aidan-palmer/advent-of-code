#include <bits/stdc++.h>

using namespace std;

vector<int> pos;

int max_val() {
    int max = 0;
    for (int i : pos) {
        if (i > max) {
            max = i;
        }
    }
    return max;
}

int burn(int x, int y) {
    if (x > y) {
        int tmp = x;
        x = y;
        y = tmp;
    }
    int sum = 0;
    for (int j = 1; j <= y - x; j++) {
        sum += j;
    }
    return sum;
}

int solve() {
    int min = INT32_MAX;
    int max = max_val();
    for (int i = 0; i <= max; i++) {
        int total = 0;
        for (int p : pos) {
            total += burn(i, p);
        }
        if (total < min) {
            min = total;
        }
    }
    return min;
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
        stringstream stream(line);
        while (getline(stream, token, ',')) {
            pos.push_back(stoi(token));
        }
    }
    cout << solve() << endl;
    return 0;
}