#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int xmas(const vector<string>& words) {
    int total = 0;
    size_t i, j;

    for (i = 0; i < words.size(); i++) {
        for (j = 0; j < words[i].size(); j++) {
            string right, left, down, up, down_right, down_left, up_right, up_left;//

            if (j + 3 < words[i].size()) {
                right = words[i].substr(j, 4);
                //cout << right << endl;

                if (right == "XMAS" || right == "SAMX") {
                    total++;
                }
            }
            if (i + 3 < words.size()) {
                down = words[i][j] + words[i + 1][j] + words[i + 2][j] + words[i + 3][j];

                if (down == "XMAS" || down == "SAMX") {
                    total++;
                }
            }
            if (i + 3 < words.size() && j + 3 < words[i].size()) {
                down_right = words[i][j] + words[i + 1][j + 1] + words[i + 2][j + 2] + words[i + 3][j + 3];

                if (down_right == "XMAS" || down_right == "SAMX") {
                    total++;
                }                
            }

            if (int(i) - 2 > 0 && int(j) - 2 > 0) {
                //cout << i - 2 << endl << j - 2 << endl;
                down_left = words[i][j] + words[i - 1][j - 1] + words[i - 2][j - 2] + words[i - 3][j - 3];

                if (down_left == "XMAS" || down_left == "SAMX") {
                    total++;
                }
            }

        }
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
    vector<string> words;

    while (getline(file, line)) {
        words.push_back(line);
    }
    cout << xmas(words) << endl;
    return 0;
}
