#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>

using namespace std;

long mul(const string& line) {
    long total = 0;
    regex pattern(R"(mul\(\s*(\d+)\s*,\s*(\d+)\s*\))");
    string::const_iterator search = line.cbegin();
    smatch match;
    int x, y;

    while (regex_search(search, line.cend(), match, pattern)) {
        try {
            x = stoi(match[1]);
            y = stoi(match[2]);
            total += x * y;
        } catch (const invalid_argument& e) {
            continue;
        }
        search = match.suffix().first;
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
    long total = 0;

    while (getline(file, line)) {
        total += mul(line);
    }
    cout << total << endl;
    return 0;
}