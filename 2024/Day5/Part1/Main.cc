#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

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
    string token;
    map<int, vector<int> > rules;
    vector<vector<int> > updates;
    size_t i, j;

    while (getline(file, line)) {
        stringstream stream(line);
        vector<int> a;

        while (getline(stream, token, '|')) {
            a.push_back(stoi(token));
        }
        if (a.size() == 2) {
            rules[a[0]].push_back(a[1]);
            a.clear();
        }

        while (getline(stream, token, ',')) {
            a.push_back(stoi(token));
        }
        if (a.size() > 0) {
            updates.push_back(a);
        }
    }
    for (i = 0; i < updates.size(); i++) {
        for (j = 0; j < updates[i].size(); j++) {
            cout << updates[i][j] << " ";
        }
        cout << endl;
    }

    //cout << total << endl;
    return 0;
}