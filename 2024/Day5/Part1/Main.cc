#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

bool contains(const vector<int>& vec, const int& target) {

}

bool is_correct(const vector<int>& update, map<int, vector<int> >& rules) {
    size_t i, j, k;
    size_t n = update.size();

    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            int key = update[i];
            int target = update[j];

            if (!contains(rules[key], target)) {
                return false;
            }
        }
    }
    return true;
}

int get_middle(const vector<int>& update) {

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
    map<int, vector<int> > rules;
    vector<vector<int> > updates;
    size_t i, j;
    long total;

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
            rules[rule[0]].push_back(rule[1]);
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
/*
    for (i = 0; i < rules.size(); i++) {
        for (j = 0; j < rules[i].size(); j++) {
            cout << rules[i][j] << " ";
        }
        cout << endl;
    }*/

    cout << total << endl;
    return 0;
}