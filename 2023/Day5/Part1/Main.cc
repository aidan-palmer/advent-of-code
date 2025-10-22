#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct Map {
    int dest;
    int source;
    int length;
};

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
    vector<int> seeds;
    vector<vector<Map>> maps;
    //int type = -1;
    vector<Map> tmp;
    while (getline(file, line)) {
        if (!line.empty()) {
            string s = line.substr(0, 5);
            if (s == "seeds") {
                line = line.substr(7);
                stringstream stream(line);
                while (getline(stream, token, ' ')) {
                    //cout << token << endl;
                    seeds.push_back(stoi(token));
                }
                continue;
            } else if (!isdigit(line[0])) {
                if (!tmp.empty()) {
                    maps.push_back(tmp);
                    tmp.clear();
                }
            } else {
                vector<int> nums;
                stringstream stream(line);
                while (getline(stream, token, ' ')) {
                    //cout << token << endl;
                    nums.push_back(stoi(token));
                }
                Map m = {nums[0], nums[1], nums[2]};
                tmp.push_back(m);
            }
        }
    }
    if (!tmp.empty()) {
        maps.push_back(tmp);
    }
    for (int s : seeds) {
        cout << s << ' ';
    }
    cout << endl << endl;
    for (vector<Map> v : maps) {
        for (Map m : v) {
            cout << m.dest << ' ' << m.source << ' ' << m.length << endl;
        }
        cout << endl;
    }

//    cout << total << endl;
    return 0;
}