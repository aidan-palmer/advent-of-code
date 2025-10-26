#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

struct Node {
    string left;
    string right;
};

long gcd(long x, long y) {
    while (y > 0) {
        long tmp = y;
        y = x % y;
        x = tmp;
    }
    return x;
}

long lcm(long x, long y) {
    return x * y / gcd(x, y);
}

long steps(string& instr, map<string, Node>& nodes, string start) {
    long total = 0;
    string next = start;
    while (next[2] != 'Z') {
        for (char c : instr) {
            if (next[2] == 'Z') {
                return total;
            }
            if (c == 'L') {
                next = nodes[next].left;
            } else {
                next = nodes[next].right;
            }
            total++;
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
    string instr;
    map<string, Node> nodes;
    bool first = true;
    while (getline(file, line)) {
        if (line.size() > 0) {
            if (first) {
                instr = line;
                first = false;
            } else {
                Node n;
                string s = line.substr(0, 3);
                n.left = line.substr(7, 3);
                n.right = line.substr(12, 3);
                nodes[s] = n;
            }
        }
    }
    vector<long> results;
    for (auto& pair : nodes) {
        if (pair.first[2] == 'A') {
            results.push_back(steps(instr, nodes, pair.first));
        }
    }
    long r = results[0];
    for (size_t i = 1; i < results.size(); i++) {
        r = lcm(r, results[i]);
    }
    cout << r << endl;
    return 0;
}