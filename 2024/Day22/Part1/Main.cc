#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void mix(long& secret, long val) {
    secret ^= val;
}

void prune(long& secret) {
    secret %= 16777216;
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
    vector<long> secrets;
    long total = 0;

    while (getline(file, line)) {
        secrets.push_back(stol(line));
    }

    for (long secret : secrets) {        
        for (int i = 0; i < 2000; i++) {
            mix(secret, secret * 64);
            prune(secret);

            mix(secret, secret / 32);
            prune(secret);

            mix(secret, secret * 2048);
            prune(secret);
        }
        //cout << secret << endl;
        total += secret;
    }

    cout << total << endl;
    return 0;
}