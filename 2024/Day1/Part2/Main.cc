#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

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
    string token;
    vector<int> a;
    vector<int> b;
    int x;

    // Read the file
    while (getline(file, line)) {
        stringstream stream(line);
        x = 0;
        // Parse each line for the two integers
        while (getline(stream, token, ' ')) {
            //cout << token << '?' << endl;
            try {
                if (!x) {
                    a.push_back(stoi(token));
                    x++;
                } else {
                    b.push_back(stoi(token));
                    x--;
                }
            } catch (const invalid_argument &e) {
                continue;
            }

        }
    }
    map<int, int> freq;
    int sim = 0;
    size_t i;

    for (i = 0; i < b.size(); i++) {
        // Check if key is already in the map
        if (freq.count(b[i]) > 0) {
            freq[b[i]]++;
        } else {
            freq[b[i]] = 1;
        }
    }

    for (i = 0; i < a.size(); i++) {
        sim += a[i] * freq[a[i]];
    }

    cout << sim << endl;
    return 0;
}