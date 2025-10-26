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

int steps(string& instr, map<string, Node>& nodes) {
    int total = 0;
    string next = "AAA";
    while (next != "ZZZ") {
        for (char c : instr) {
            if (next == "ZZZ") {
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
    cout << steps(instr, nodes) << endl;
    return 0;
}