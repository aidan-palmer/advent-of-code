#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <climits>

using namespace std;

struct Map {
    long dest;
    long source;
    long length;
};

long location(long seed, vector<vector<Map>> maps) {
    for (vector<Map> v : maps) {
        for (Map m : v) {
            if (seed >= m.source && seed < m.source + m.length) {
                long diff = m.dest - m.source;
                seed += diff;
                break;
            }
        }
    }
    return seed;
}

long min_loc(long seed, long range, vector<vector<Map>> maps) {
    long min = LONG_MAX;
    for (long i = seed; i < seed + range; i++) {
        long loc = location(i, maps);
        if (loc < min) {
            min = loc;
        }
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
    vector<long> seeds;
    vector<vector<Map>> maps;
    vector<Map> tmp;
    while (getline(file, line)) {
        if (!line.empty()) {
            string s = line.substr(0, 5);
            if (s == "seeds") {
                line = line.substr(7);
                stringstream stream(line);
                while (getline(stream, token, ' ')) {
                    seeds.push_back(stol(token));
                }
                continue;
            } else if (!isdigit(line[0])) {
                if (!tmp.empty()) {
                    maps.push_back(tmp);
                    tmp.clear();
                }
            } else {
                vector<long> nums;
                stringstream stream(line);
                while (getline(stream, token, ' ')) {
                    nums.push_back(stol(token));
                }
                Map m = {nums[0], nums[1], nums[2]};
                tmp.push_back(m);
            }
        }
    }
    if (!tmp.empty()) {
        maps.push_back(tmp);
    }
    long min = LONG_MAX;
    for (size_t i = 0; i < seeds.size() - 1; i += 2) {
        long loc = min_loc(seeds[i], seeds[i + 1], maps);
        if (loc < min) {
            min = loc;
        }
    }
    cout << min << endl;
    return 0;
}