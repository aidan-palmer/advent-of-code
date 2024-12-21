#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>
#include <cstdint>
#include <climits>
#include <algorithm>

using namespace std;

vector<string> patterns;
vector<size_t> pattern_lengths;
int result = 0;

bool contains(string x) {
    for (size_t i = 0; i < patterns.size(); i++) {
        if (patterns[i] == x) {
            return true;
        }
    }
    return false;
}

void is_possible(string design) {
    if (design.empty()) {
        result++;
        return;
    }

    for (size_t len : pattern_lengths) {
        if (len <= design.size()) {
            string sub = design.substr(0, len);

            if (contains(sub)) {
                is_possible(sub);
            }
        }
    }
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
    vector<string> designs;
    bool is_pattern = true;
    int total = 0;
    size_t i;

    while (getline(file, line)) {
        if (line.empty()) {
            is_pattern = false;
            continue;
        }

        if (is_pattern) {
            stringstream stream(line);

            while (getline(stream, token, ' ')) {
                patterns.push_back(token.substr(0, token.size() - 1));
            }
        } else {
            designs.push_back(line);
        }
    }
    file.close();
/*
    for (i = 0; i < patterns.size(); i++) {
        cout << patterns[i] << " ";
    }
    cout << endl;

    for (i = 0; i < designs.size(); i++) {
        cout << designs[i] << " ";
    }
    cout << endl;
*/

    for (i = 0; i < patterns.size(); i++) {
        pattern_lengths.push_back(patterns[i].size());
    }
    sort(pattern_lengths.begin(), pattern_lengths.end());

    for (i = 0; i < designs.size(); i++) {
        result = 0;
        is_possible(designs[i]);

        if (result > 0) {
            total++;
        }
    }

    cout << total << endl;
    return 0;
}