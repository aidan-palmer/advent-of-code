#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <list>

using namespace std;
/*
class Graph {
    struct node {
        string name;
        vector<node> edges;
    };

    public:

};
*/
bool contains_t(list<string> nodes) {
    for (string node : nodes) {
        if (node[0] == 't') {
            return true;
        }
    }
    return false;
}

bool contains_t(string node) {
    return node[0] == 't';
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
    map<string, list<string>> network;

    while (getline(file, line)) {
        stringstream stream(line);
        vector<string> conn;

        while (getline(stream, token, '-')) {
            conn.push_back(token);
        }
        network[conn[0]].push_back(conn[1]);
        network[conn[1]].push_back(conn[0]);
    }

    for (const auto& net : network) {
       // if (contains_t(net.first) || contains_t(net.second)) {
            cout << net.first << " ";

            for (const auto& con : net.second) {
                cout << con << " ";
            }
            cout << endl;
       // }
    }

//    cout << total << endl;
    return 0;
}