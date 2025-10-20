#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <string>
#include <map>

using namespace std;

bool is_valid(int row, int start, int end, vector<string>& grid) {

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
        
    }

//    cout << total << endl;
    return 0;
}