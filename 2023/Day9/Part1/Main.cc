#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool all_zero(vector<int>& x) {
    for (int i : x) {
        if (i != 0) {
            return false;
        }
    }
    return true;
}

long next_val(vector<int>& hist) {
    vector<vector<int>> seq;
    seq.push_back(hist);
    while (!all_zero(seq[seq.size() - 1])) {
        vector<int> next;
        int n = seq[seq.size() - 1].size();
        int m = seq.size();
        for (int i = 0; i < n - 1; i++) {
            next.push_back(seq[m - 1][i + 1] - seq[m - 1][i]);
        }
        seq.push_back(next);
    }
    long next = 0;
    for (int i = int(seq.size()) - 2; i >= 0; i--) {
        int n = seq[i].size();
        next += seq[i][n - 1];
    }
    return next;
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
    vector<vector<int>> report;
    while (getline(file, line)) {
        stringstream stream(line);
        vector<int> history;
        while (getline(stream, token, ' ')) {
            history.push_back(stoi(token));
        }
        report.push_back(history);
    }
    for (vector<int> r : report) {
        total += next_val(r);
    }
    cout << total << endl;
    return 0;
}