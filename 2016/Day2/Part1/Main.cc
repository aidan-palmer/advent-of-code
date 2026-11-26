#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> keypad = {
    {1, 2, 3}, 
    {4, 5, 6},
    {7, 8, 9}
};

int keypad_size = 3;

pair<int, int> find_button_coordinates(int row, int col, string& line) {
    for (const char& c : line) {
        switch (c) {
            case 'U':
            {
                if (row > 0) {
                    row--;
                }
                break;
            }
            case 'D':
            {
                if (row < keypad_size - 1) {
                    row++;
                }
                break;
            }
            case 'L':
            {
                if (col > 0) {
                    col--;
                }
                break;
            }
            case 'R':
            {
                if (col < keypad_size - 1) {
                    col++;
                }
                break;
            }
        }
    }
    return make_pair(row, col);
}

int get_button(pair<int, int>& coordinates) {
    return keypad[coordinates.first][coordinates.second];
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
    vector<int> code;
    int prev_row = 1;
    int prev_col = 1;
    pair<int, int> coordinates;

    while (getline(file, line)) {
        coordinates = find_button_coordinates(prev_row, prev_col, line);
        prev_row = coordinates.first;
        prev_col = coordinates.second;
        int button = get_button(coordinates);
        code.push_back(button);
    }
    for (const int& i : code) {
        cout << i;
    }
    cout << endl;
    return 0;
}