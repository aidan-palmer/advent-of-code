#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

int race(int time, int distance) {
    int count = 0;
    for (int i = 1; i < time; i++) {
        int dist = i * (time - i);
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
    vector<int> time;
    vector<int> distance;
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
                time.push_back(stoi(num));
            } else {
                distance.push_back(stoi(num));
            }
            line = match.suffix().str();
        }
    }
    int prod = 1;
    for (size_t i = 0; i < time.size(); i++) {
        int records = race(time[i], distance[i]);
        prod *= records;
    }
    cout << prod << endl;
    return 0;
}