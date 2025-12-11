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

map<string, vector<string>> devices;
map<tuple<string, bool, bool>, size_t> cache;

size_t paths(string dev, bool dac, bool fft) {
    if (dev == "out") {
        if (dac && fft) {
            return 1;
        }
        return 0;
    }
    bool ndac = dac || (dev == "dac");
    bool nfft = fft || (dev == "fft");
    auto key = make_tuple(dev, ndac, nfft);
    if (cache.count(key)) {
        return cache[key];
    }
    size_t total = 0;
    for (string s : devices[dev]) {
        total += paths(s, ndac, nfft);
    }
    cache[key] = total;
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
    while (getline(file, line)) {
        int col = index_of(line, ':');
        string key = line.substr(0, col);
        line = line.substr(col + 2);
        stringstream stream(line);
        vector<string> v;
        while (getline(stream, token, ' ')) {
            v.push_back(token);
        }
        devices[key] = v;
    }
    cout << paths("svr", false, false) << endl;
    return 0;
}