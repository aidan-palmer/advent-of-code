#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

struct Lens {
    int lhash;
    int focal;
    string label;
};

map<int, vector<Lens>> boxes;

int hash_(string s) {
    int x = 0;
    for (char c : s) {
        x += c;
        x *= 17;
        x %= 256;
    }
    return x;
}

string get_label(string s, int end) {
    return s.substr(0, end);
}

int index_op(string s) {
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '=' || s[i] == '-') {
            return i;
        }
    }
    return -1;
}

void rm_lens(string label, int lhash) {
    for (size_t i = 0; i < boxes[lhash].size(); i++) {
        if (boxes[lhash][i].label == label) {
            boxes[lhash].erase(boxes[lhash].begin() + i);
            return;
        }
    }
}

// Returns -1 if not present in boxes
int lens_loc(string label, int lhash) {
    for (size_t i = 0; i < boxes[lhash].size(); i++) {
        if (boxes[lhash][i].label == label) {
            return i;
        }
    }
    return -1;
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
        stringstream stream(line);
        while (getline(stream, token, ',')) {
            int op_index = index_op(token);
            string label = get_label(token, op_index);
            int lhash = hash_(label);
            char op = token[op_index];
            //cout << "Label: " << lbl << " Op: " << op << endl;
            if (op == '-') {
                rm_lens(label, lhash);
            } else {
                int focal = stoi(token.substr(op_index + 1));
                Lens lens;
                lens.lhash = lhash;
                lens.focal = focal;
                lens.label = label;
                int loc = lens_loc(label, lhash);
                if (loc == -1) {
                    boxes[lhash].push_back(lens);
                } else {
                    boxes[lhash][loc] = lens;
                }
            }
        }
    }
    for (const auto& pair : boxes) {
        for (size_t i = 0; i < pair.second.size(); i++) {
            int power = 1 + pair.first;
            power *= i + 1;
            power *= pair.second[i].focal;
            total += power;
        }
    }
    cout << total << endl;
    return 0;
}