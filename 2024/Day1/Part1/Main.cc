#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

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
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int total = 0;

    for (size_t i = 0; i < a.size(); i++) {
        total += abs(a[i] - b[i]);
    }
    cout << total << endl;
    return 0;
}