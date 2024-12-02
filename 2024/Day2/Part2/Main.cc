#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

bool isIncreasing(vector<int> vec) {
    vector<int> copy(vec);
    sort(copy.begin(), copy.end());

    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] != copy[i]) {
            return false;
        }
    }
    return true;
}

bool isDecreasing(vector<int> vec) {
    vector<int> copy(vec);
    sort(copy.begin(), copy.end(), greater<int>());

    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] != copy[i]) {
            return false;
        }
    }
    return true;
}

bool isSafe(vector<int> a) {
    if (isIncreasing(a) || isDecreasing(a)) {
        for (size_t i = 0; i < a.size() - 1; i++) {
            int distance = abs(a[i] - a[i + 1]);
            if (distance > 3 || distance == 0) {
                return false;
            }
        }
        return true;
    }
    return false;
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

    // Read the file
    while (getline(file, line)) {
        stringstream stream(line);
        vector<int> a;
        // Parse each line for the integers
        while (getline(stream, token, ' ')) {
            try {
                a.push_back(stoi(token));
            } catch (const invalid_argument &e) {
                continue;
            }
        }
        if (isSafe(a)) {
            total++;
        } else {
            for (size_t i = 0; i < a.size(); i++) {
                vector<int> copy(a);
                copy.erase(copy.begin() + i);
                if (isSafe(copy)) {
                    total++;
                    break;
                }
            }
        }
    }
    cout << total << endl;
    return 0;
}