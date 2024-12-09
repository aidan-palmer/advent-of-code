#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

bool is_correct(const vector<int>& update, const map<int, set<int>>& rules) {
    map<int, int> position;

    for (size_t i = 0; i < update.size(); i++) {
        position[update[i]] = i;
    }

    for (const auto& rule : rules) {
        int key = rule.first;
        const set<int>& targets = rule.second;

        if (position.find(key) == position.end()) {
            continue;
        }

        for (int target : targets) {
            if (position.find(target) != position.end() && position[key] > position[target]) {
                return false;
            }
        }
    }
    return true;
}

int get_middle(const vector<int>& update) {
    return update[update.size() / 2];
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
    map<int, set<int>> rules;
    vector<vector<int>> updates;
    size_t i;
    long total = 0;

    while (getline(file, line)) {
        if (line.empty()) {
            break;
        }
        stringstream stream(line);
        vector<int> rule;

        while (getline(stream, token, '|')) {
            rule.push_back(stoi(token));
        }
        if (rule.size() == 2) {
            rules[rule[0]].insert(rule[1]);
        }
    }

    while (getline(file, line)) {
        stringstream stream(line);
        vector<int> update;

        while (getline(stream, token, ',')) {
            update.push_back(stoi(token));
        }
        if (!update.empty()) {
            updates.push_back(update);
        }
    }

    for (i = 0; i < updates.size(); i++) {
        if (is_correct(updates[i], rules)) {
            total += get_middle(updates[i]);
        }
    }

    cout << total << endl;
    return 0;
}