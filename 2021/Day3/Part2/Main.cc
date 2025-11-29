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
    string gamma;
    string epsilon;
    vector<string> report;
    size_t i, j;
    while (getline(file, line)) {
        report.push_back(line);
    }
    for (i = 0; i < report[0].size(); i++) {
        int zero = 0;
        int one = 0;
        for (j = 0; j < report.size(); j++) {
            if (report[j][i] == '0') {
                zero++;
            } else {
                one++;
            }
        }
        if (zero > one) {
            gamma += '0';
            epsilon += '1';
        } else {
            gamma += '1';
            epsilon += '0';
        }
    }
    int g = stoi(gamma, nullptr, 2);
    int e = stoi(epsilon, nullptr, 2);
    cout << g * e << endl;
    return 0;
}