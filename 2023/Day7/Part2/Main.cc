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

map<char, int> strength = {{'2', 0}, {'3', 1}, {'4', 2}, {'5', 3}, {'6', 4}, 
    {'7', 5}, {'8', 6}, {'9', 7}, {'T', 8}, {'J', -1}, {'Q', 10}, {'K', 11}, {'A', 12}};

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
   // cout << h.cards << " Number of J's: " << freq['J'] << endl;
    int threes = 0;
    int twos = 0;
    if (freq['J'] > 0) {
        char max_ch = ' ';
        int max = -1;
        int j = freq['J'];
        freq['J'] = 0;
        for (const auto& m : freq) {
            if (m.second > max) {
                max = m.second;
                max_ch = m.first;
            }
        }
        freq[max_ch] += j;
        //cout << "Max frequency: " << max << " " << char(max_ch) << endl;
        //freq['J'] = 0;
    }
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

// Returns true if x > y
bool greatr(Hand x, Hand y) {
    for (int i = 0; i < 5; i++) {
        if (x.cards[i] != y.cards[i]) {
            if (strength[x.cards[i]] > strength[y.cards[i]]) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

void sort(vector<Hand>& hands) {
    for (size_t i = 1; i < hands.size(); i++) {
        Hand key = hands[i];
        int j = i - 1;
        while (j >= 0 && greatr(hands[j], key)) {
            hands[j + 1] = hands[j];
            j--;
        }
        hands[j + 1] = key;
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
        //cout << h.cards << " Type: " << t << endl;
    }
    long long rank = 1;
    long long total = 0;
    for (int i = 0; i < 7; i++) {
        sort(types[i]);
        for (Hand h : types[i]) {
            total += rank * h.bid;
            rank++;
            //cout << h.cards << " " << h.bid << endl;
        }
    }
    cout << total << endl;
    return 0;
}