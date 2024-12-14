#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool even_length(size_t x) {
    string s = to_string(x);
    return s.size() % 2 == 0;
}

vector<size_t> split(size_t x) {
    string s = to_string(x);
    string a = s.substr(0, s.size() / 2);
    string b = s.substr(s.size() / 2);

    vector<size_t> result;
    result.push_back(stoi(a));
    result.push_back(stoi(b));
    return result;
}

void blink(vector<size_t>& stones) {
    for (size_t i = 0; i < stones.size(); i++) {
        if (stones[i] == 0) {
            stones[i] = 1;
        } else if (even_length(stones[i])) {
            vector<size_t> spl = split(stones[i]);
            stones[i] = spl[0];
            stones.insert(stones.begin() + i + 1, spl[1]);
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
    vector<size_t> stones;

    while (getline(file, line)) {
        stringstream stream(line);

        while (getline(stream, token, ' ')) {
            stones.push_back(stoi(token));
        }
    }

    for (size_t i = 0; i < 25; i++) {
        blink(stones);
    }

    cout << stones.size() << endl;
    return 0;
}