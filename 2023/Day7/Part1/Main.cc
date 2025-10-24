#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

struct Hand {
    string cards;
    int bid;
};

map<char, int> strength;

int index_of(string s, char c) {
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            return i;
        }
    }
    return -1;
}

// 0 = high card, five of a kind = 6, etc.
int type(Hand h) {
    map<char, int> freq; // key: card, value: frequency
    for (char c : h.cards) {
        freq[c]++;
    }
    int threes = 0;
    int twos = 0;
    for (const auto& m : freq) {
        if (m.second == 5) {
            return 6;
        } else if (m.second == 4) {
            return 5;
        } else if (m.second == 3) {
            threes++;
        } else if (m.second == 2) {
            twos++;
        }
    }
    if (threes > 0 && freq.size() == 2) {
        return 4;
    } else if (threes > 0 && freq.size() == 3) {
        return 3;
    } else if (twos == 2) {
        return 2;
    } else if (twos == 1) {
        return 1;
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
    string token;
    vector<Hand> hands;
    while (getline(file, line)) {
        int space = index_of(line, ' ');
        Hand h;
        h.cards = line.substr(0, space);
        h.bid = stoi(line.substr(space + 1));
        hands.push_back(h);
    }
    // Put the hands into buckets based on type
    vector<Hand> types[7];
    for (Hand h : hands) {
        int t = type(h);
        types[t].push_back(h);
    }
    for (int i = 0; i < 7; i++) {
        for (Hand h : types[i]) {
            cout << h.cards << endl;
        }
    }

//    cout << total << endl;
    return 0;
}