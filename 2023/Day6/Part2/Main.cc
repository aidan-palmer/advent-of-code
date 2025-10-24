#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

long race(long time, long distance) {
    long count = 0;
    for (long i = 1; i < time; i++) {
        long dist = i * (time - i);
        if (dist > distance) {
            count++;
        }
    }
    return count;
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
    vector<int> times;
    vector<int> distances;
    smatch match;
    regex pattern("\\d+");
    string num;
    bool is_time = false;
    while (getline(file, line)) {
        if (line.substr(0, 4) == "Time") {
            is_time = true;
        } else {
            is_time = false;
        }
        while (regex_search(line, match, pattern)) {
            num = match.str(0);
            if (is_time) {
                times.push_back(stoi(num));
            } else {
                distances.push_back(stoi(num));
            }
            line = match.suffix().str();
        }
    }
    string t;
    string d;
    for (size_t i = 0; i < times.size(); i++) {
        t += to_string(times[i]);
        d += to_string(distances[i]);
    }
    long time = stol(t);
    long distance = stol(d);
    long ways = race(time, distance);
    cout << ways << endl;
    return 0;
}