#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <string>
#include <map>

using namespace std;

bool is_symbol(char c) {
    if (!isdigit(c) && c != '.') {
        return true;
    }
    return false;
}

bool is_valid(int row, int start, int end, vector<string>& grid) {
    for (int i = start; i <= end; i++) {
        // Up
        if (row - 1 >= 0 && is_symbol(grid[row - 1][i])) {
            return true;
        }
        // Down
        if (row + 1 < grid.size() && is_symbol(grid[row + 1][i])) {
            return true;
        }
        // Left
        if (i == start && i - 1 >= 0 && is_symbol(grid[row][i - 1])) {
            return true;
        }
        // Right
        if (i == end && i + 1 < grid[row].size() && is_symbol(grid[row][i + 1])) {
            return true;
        }
        // Right-Up
        if (i == end && i + 1 < grid[row].size() && row - 1 >= 0 && is_symbol(grid[row - 1][i + 1])) {
            return true;
        }
        // Right-Down
        if (i == end && i + 1 < grid[row].size() && row + 1 < grid.size() && is_symbol(grid[row + 1][i + 1])) {
            return true;
        }
        // Left-Up
        if (i == start && i - 1 >= 0 && row - 1 >= 0 && is_symbol(grid[row - 1][i - 1])) {
            return true;
        }
        // Left-Down
        if (i == start && i - 1 >= 0 && row + 1 < grid.size() && is_symbol(grid[row + 1][i - 1])) {
            return true;
        }
    }
    return false;
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
    // key vector structure is row, start_col, end_col. value is part number
    map<vector<int>, int> parts;
    vector<string> grid;
    int row = 0;
    while (getline(file, line)) {
        grid.push_back(line);
        int start, end;
        string num;
        for (size_t i = 0; i < line.size(); i++) {
            if (isdigit(line[i])) {
                if (num.size() == 0) {
                    start = i;
                }
                num += line[i];
            } else {
                if (num.size() > 0) {
                    end = i - 1;
                    vector<int> vec;
                    vec.push_back(row);
                    vec.push_back(start);
                    vec.push_back(end);
                    parts[vec] = stoi(num);
                }
                num.clear();
            }
        }
        row++;
    }
    for (const auto& pair : parts) {
        //cout << pair.second << endl;
        if (is_valid(pair.first[0], pair.first[1], pair.first[2], grid)) {
            total += pair.second;
        }
    }
    cout << total << endl;
    return 0;
}