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
    vector<string> oxygen;
    vector<string> scrubber;
    size_t i, j;
    while (getline(file, line)) {
        oxygen.push_back(line);
        scrubber.push_back(line);
    }
    string ogr;
    for (i = 0; i < oxygen[0].size(); i++) {
        int zero = 0;
        int one = 0;
        for (j = 0; j < oxygen.size(); j++) {
            if (oxygen[j][i] == '0') {
                zero++;
            } else {
                one++;
            }
        }
        if (zero > one) {
            for (j = 0; j < oxygen.size(); j++) {
                if (oxygen[j][i] == '1') {
                    oxygen.erase(oxygen.begin() + j);
                    j--;
                }
            }
        } else {
            for (j = 0; j < oxygen.size(); j++) {
                if (oxygen[j][i] == '0') {
                    oxygen.erase(oxygen.begin() + j);
                    j--;
                }
            }
        }
        if (oxygen.size() == 1) {
            ogr = oxygen[0];
        }
    }
    string scr;
    for (i = 0; i < scrubber[0].size(); i++) {
        int zero = 0;
        int one = 0;
        for (j = 0; j < scrubber.size(); j++) {
            if (scrubber[j][i] == '0') {
                zero++;
            } else {
                one++;
            }
        }
        if (zero > one) {
            for (j = 0; j < scrubber.size(); j++) {
                if (scrubber[j][i] == '0') {
                    scrubber.erase(scrubber.begin() + j);
                    j--;
                }
            }
        } else {
            for (j = 0; j < scrubber.size(); j++) {
                if (scrubber[j][i] == '1') {
                    scrubber.erase(scrubber.begin() + j);
                    j--;
                }
            }
        }
        if (scrubber.size() == 1) {
            scr = scrubber[0];
        }
    }
    int o = stoi(ogr, nullptr, 2);
    int s = stoi(scr, nullptr, 2);
    cout << o * s << endl;
    return 0;
}