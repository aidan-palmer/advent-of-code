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
            if (i + 3 < words.size() && j > 2) {
                down_left = words[i][j] + words[i + 1][j - 1] + words[i + 2][j - 2] + words[i + 3][j - 3];
                if (down_left == "XMAS" || down_left == "SAMX") {
                    total++;
                }
            }
            if (j > 2) {
                left = words[i].substr(j - 3, 4);
                if (left == "XMAS" || left == "SAMX") {
                    total++;
                }
            }
            if (i > 2) {
                up = words[i][j] + words[i - 1][j] + words[i - 2][j] + words[i - 3][j];
                if (up == "XMAS" || up == "SAMX") {
                    total++;
                }
            }
            if (i > 2 && j > 2) {
                up_left = words[i][j] + words[i - 1][j - 1] + words[i - 2][j - 2] + words[i - 3][j - 3];
                if (up_left == "XMAS" || up_left == "SAMX") {
                    total++;
                }
            }
            if (i > 2 && j + 3 < words[i].size()) {
                up_right = words[i][j] + words[i - 1][j + 1] + words[i - 2][j + 2] + words[i - 3][j + 3];
                if (up_right == "XMAS" || up_right == "SAMX") {
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
