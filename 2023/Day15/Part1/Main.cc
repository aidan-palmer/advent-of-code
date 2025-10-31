#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int hash_(string& s) {
    int x = 0;
    for (char c : s) {
        x += c;
        x *= 17;
        x %= 256;
    }
    return x;
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
            total += hash_(token);
        }
    }
    cout << total << endl;
    return 0;
}