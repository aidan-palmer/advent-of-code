#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <map>
#include <chrono>

using namespace std;

map<ulong, tuple<ulong, ulong>> cache;

bool contains(ulong x) {
    for (const auto& pair : cache) {
        if (pair.first == x) {
            return true;
        }
    }
    return false;
}

bool even_length(ulong x) {
    string s = to_string(x);
    return s.size() % 2 == 0;
}

vector<ulong> split(ulong x) {
    string s = to_string(x);
    string a = s.substr(0, s.size() / 2);
    string b = s.substr(s.size() / 2);

    vector<ulong> result;
    result.push_back(stoi(a));
    result.push_back(stoi(b));
    return result;
}

void blink(vector<ulong>& stones) {
    for (size_t i = 0; i < stones.size(); i++) {
        if (stones[i] == 0) {
            stones[i] = 1;
        } else if (even_length(stones[i])) {
            ulong a, b;
            if (contains(stones[i])) {
                a = get<0>(cache[stones[i]]);
                b = get<1>(cache[stones[i]]);
            } else {
                vector<ulong> spl = split(stones[i]);
                a = spl[0];
                b = spl[1];
                cache[stones[i]] = make_tuple(a, b);
            }
            stones[i] = a;
            stones.insert(stones.begin() + i + 1, b);
            i++;            
        } else {
            stones[i] *= 2024;
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
    vector<ulong> stones;

    while (getline(file, line)) {
        stringstream stream(line);

        while (getline(stream, token, ' ')) {
            stones.push_back(stoi(token));
        }
    }
    auto start = chrono::steady_clock::now();

    for (uint i = 0; i < 75; i++) {
        blink(stones);
        cout << "Progress: iteration " << i << endl;
    }
    auto end = chrono:: steady_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Program duration: " << elapsed.count() << endl;

    cout << stones.size() << endl;
    return 0;
}