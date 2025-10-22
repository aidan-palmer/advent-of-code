#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <map>

using namespace std;

struct Card {
    int quant;
    int matches;
};

bool is_in(vector<int> nums, int x) {
    for (int y : nums) {
        if (y == x) {
            return true;
        }
    }
    return false;
}

int total_cards(map<int, Card>& data, int n) {
    for (int i = 1; i <= n; i++) {
        if (data[i].matches > 0) {
            for (int k = 0; k < data[i].quant; k++) {
                for (int j = i + 1; j <= n && j <= i + data[i].matches; j++) {
                    data[j].quant++;
                }
            }
        }
    }
    int total = 0;
    for (int i = 1; i <= n; i++) {
        total += data[i].quant;
    }
    return total;
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
    int card_num = 1;
    map<int, Card> data; // line number, Card struct
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
        Card card = {1, count};
        data[card_num] = card;
        card_num++;
    }
    cout << total_cards(data, card_num - 1) << endl;
    return 0;
}