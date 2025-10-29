#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<string> records;
vector<vector<int>> backup;

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
    while (getline(file, line)) {
        stringstream stream(line);
        bool first = true;
        while (getline(stream, token, ' ')) {
            if (first) {
                records.push_back(token);
                first = false;
            } else {
                stringstream s(token);
                vector<int> v;
                string t;
                while (getline(s, t, ',')) {
                    v.push_back(stoi(t));
                }
                backup.push_back(v);
            }
        }
    }

    for (string s : records) {
        cout << s << endl;
    }
    for (vector<int> v : backup) {
        for (int i : v) {
            cout << i << " ";
        }
        cout << endl;
    }
    /**
     * Parsed input, can't figure out how to do this puzzle.
     */

//    cout << total << endl;
    return 0;
}