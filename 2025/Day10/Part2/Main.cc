#include <bits/stdc++.h>

using namespace std;

int index_of(string s, char c) {
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            return i;
        }
    }
    return -1;
}

int max(vector<int>& v) {
    int mx = -1;
    for (int i : v) {
        if (i > mx) {
            mx = i;
        }
    }
    return mx;
}

vector<bool> stob(string s) {
    vector<bool> b;
    for (char c : s) {
        if (c == '.') {
            b.push_back(false);
        } else {
            b.push_back(true);
        }
    }
    return b;
}

vector<vector<int>> power_set(int n) {
    vector<vector<int>> ps;
    for (int i = 0; i < (1 << n); i++) {
        vector<int> v;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                v.push_back(j);
            }
        }
        ps.push_back(v);
    }
    return ps;
}

int fewest_presses(vector<vector<int>>& buttons, vector<int>& goal) {
    vector<vector<int>> ps = power_set(buttons.size());
    int min = INT32_MAX;
    for (vector<int> v : ps) {
        int n = v.size();
        vector<int> jolts(goal.size(), 0);
        for (int i : v) {
            for (int j : buttons[i]) {
                //b[j] = !b[j];
            }
        }
        /*
        if (b == goal && n < min) {
            min = n;
        }*/
    }
    return min;
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
    int total = 0;
    while (getline(file, line)) {
        vector<vector<int>> buttons;
        int cb = index_of(line, ']');
        vector<int> jolts;  
        string j = line.substr(index_of(line, '{') + 1);
        j = j.substr(0, j.size() - 1);
        stringstream str(j);
        while (getline(str, token, ',')) {
            jolts.push_back(stoi(token));
        }
        line = line.substr(0, index_of(line, '{') - 1);
        line = line.substr(cb + 2);
        stringstream stream(line);
        while (getline(stream, token, ' ')) {
            vector<int> button;
            token = token.substr(1, token.size() - 2);
            stringstream s(token);
            string t;
            while (getline(s, t, ',')) {
                button.push_back(stoi(t));
            }
            buttons.push_back(button);
        }
        total += fewest_presses(buttons, jolts);
    }
    cout << total << endl;
    return 0;
}