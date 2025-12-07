#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> wrs;
vector<char> ops;
vector<string> mat;

bool all_space(size_t j) {
    for (size_t i = 0; i < mat.size(); i++) {
        if (mat[i][j] != ' ') {
            return false;
        }
    }
    return true;
}

void parse_nums() {
    vector<int> tmp;
    for (size_t j = 0; j < mat[0].size(); j++) {
        if (all_space(j)) {
            wrs.push_back(tmp);
            tmp.clear();
        } else {
            string s;
            for (size_t i = 0; i < mat.size(); i++) {
                if (mat[i][j] != ' ') {
                    s.push_back(mat[i][j]);
                }
            }
            tmp.push_back(stoi(s));
        }
    }
    wrs.push_back(tmp);
}

vector<char> parse_chars(string& s) {
    vector<char> v;
    for (char c : s) {
        if (c == '*' || c == '+') {
            v.push_back(c);
        }
    }
    return v;
}

long grand_total() {
    long total = 0, subtotal;
    size_t i, j;
    for (i = 0; i < wrs.size(); i++) {
        switch (ops[i]) {
            case '+':
            {
                subtotal = 0;
                for (j = 0; j < wrs[i].size(); j++) {
                    subtotal += wrs[i][j];
                }
                total += subtotal;
                break;
            }
            case '*':
            {
                subtotal = 1;
                for (j = 0; j < wrs[i].size(); j++) {
                    subtotal *= wrs[i][j];
                }
                total += subtotal;
                break;
            }
        }
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
    while (getline(file, line)) {
        if (!line.empty() && line[0] == '*') {
            ops = parse_chars(line);
        } else {
            mat.push_back(line);
        }
    }
    parse_nums();
    cout << grand_total() << endl;
    return 0;
}