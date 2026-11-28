#include <bits/stdc++.h>

using namespace std;


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
    vector<string> messages;

    while (getline(file, line)) {
        messages.push_back(line);
    }
    size_t row, col;
    string message = "";

    for (col = 0; col < messages[0].size(); col++) {
        map<char, int> freq;

        for (row = 0; row < messages.size(); row++) {
            freq[messages[row][col]]++;
        }
        char least_freq = messages[0][col];
        int lf_count = freq[least_freq];

        for (const auto& f : freq) {
            if (f.second < lf_count) {
                least_freq = f.first;
                lf_count = f.second;
            }
        }
        message.push_back(least_freq);
    }
    cout << message << endl;
    return 0;
}