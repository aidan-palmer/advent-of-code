#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> wrs;
vector<char> ops;

vector<int> parse_nums(string& s) {
    smatch match;
    regex r("[-+]?\\d+");
    vector<int> v;
    while (regex_search(s, match, r)) {
        v.push_back(stoi(match.str(0)));
        s = match.suffix().str();
    }
    return v;
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
    for (j = 0; j < wrs[0].size(); j++) {
        switch (ops[j]) {
            case '+':
            {
                subtotal = 0;
                for (i = 0; i < wrs.size(); i++) {
                    subtotal += wrs[i][j];
                }
                total += subtotal;
                break;
            }
            case '*':
            {
                subtotal = 1;
                for (i = 0; i < wrs.size(); i++) {
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
            wrs.push_back(parse_nums(line));
        }
    }
    cout << grand_total() << endl;
    return 0;
}