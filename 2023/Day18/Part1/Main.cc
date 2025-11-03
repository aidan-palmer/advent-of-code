#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<pair<char, int>> instr;
vector<vector<char>> grid;

int index_of(string s, char c) {
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            return i;
        }
    }
    return -1;
}

// Additive factorial
int af(int x) {
    int sum = 0;
    while (x > 0) {
        sum += x;
        x--;
    }
    return sum;
}

void make_edge() {
    int curr_i = 0;
    int curr_j = 0;
    for (auto& p : instr) {
        if (p.first == 'R') {
            
        }
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
    while (getline(file, line)) {
        stringstream stream(line);
        int it = 0;
        char c = ' ';
        int ins = 0;
        while (getline(stream, token, ' ')) {
            if (it == 0) {
                c = token[0];
            } else if (it == 1) {
                ins = stoi(token);
                break;
            }
            it++;
        }
        instr.push_back(make_pair(c, ins));
    }
    make_edge();



    int total = 0;
    for (auto& i : instr) {
        cout << i.first << " " << i.second << endl;
    }
   // cout << total << endl;
    return 0;
}