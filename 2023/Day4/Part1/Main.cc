#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

bool is_in(vector<int> nums, int x) {
    for (int y : nums) {
        if (y == x) {
            return true;
        }
    }
    return false;
}

int doubled(int x) {
    int y = 1;
    for (int i = 1; i < x; i++) {
        y *= 2;
    }
    return y;
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
    while (getline(file, line)) {
        size_t start = line.find(':');
        line = line.substr(start + 1);
        size_t mid = line.find('|');
        string first_half = line.substr(0, mid);
        string sec_half = line.substr(mid + 1);
        vector<int> wins;
        vector<int> haves;
        smatch match;
        regex pattern("\\d+");
        string num;
        while (regex_search(first_half, match, pattern)) {
            num = match.str(0);
            wins.push_back(stoi(num));
            first_half = match.suffix().str();
        }        
        while (regex_search(sec_half, match, pattern)) {
            num = match.str(0);
            haves.push_back(stoi(num));
            sec_half = match.suffix().str();
        }
        int count = 0;
        for (int have : haves) {
            if (is_in(wins, have)) {
                count++;
            }
        }
        if (count > 0) {
            total += doubled(count);
        }
    }
    cout << total << endl;
    return 0;
}