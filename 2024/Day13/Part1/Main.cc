#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

#define ACOST 3
#define BCOST 1

struct prize {
    uint btn_a_x, btn_a_y, btn_b_x, btn_b_y, prize_x, prize_y;
};

uint cheapest(prize& p) { 
    vector<uint> results;

    for (uint a = 1; a < 101; a++) {
        for (uint b = 1; b < 101; b++) {
            if (p.btn_a_x * a + p.btn_b_x * b == p.prize_x &&
                p.btn_a_y * a + p.btn_b_y * b == p.prize_y) {
                    results.push_back(a * ACOST + b * BCOST);
                }
        }
    }
    if (!results.empty()) {
        sort(results.begin(), results.end());
        return results[0];
    }
    return 0;
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
    vector<prize> prizes;
    prize p;
    ulong total = 0;

    while (getline(file, line)) {
        // Make sure there are two empty lines at end of input file!
        if (line.empty()) {
            prizes.push_back(p);
            continue;
        }
        size_t com = line.find(',');
        // who needs regex?
        if (line[7] == 'A') {
            p.btn_a_x = stoi(line.substr(12, com - 12));
            p.btn_a_y = stoi(line.substr(com + 4));
        } else if (line[7] == 'B') {
            p.btn_b_x = stoi(line.substr(12, com - 12));
            p.btn_b_y = stoi(line.substr(com + 4));
        } else if (line[7] == 'X') {
            p.prize_x = stoi(line.substr(9, com - 9));
            p.prize_y = stoi(line.substr(com + 4));
        }
    }

    for (size_t i = 0; i < prizes.size(); i++) {
        total += cheapest(prizes[i]);
    }

    cout << total << endl;
    return 0;
}