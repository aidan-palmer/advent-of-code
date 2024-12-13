#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

// Rotate matrix by 90 degrees
vector<vector<uint>> rotate(vector<vector<uint>>& grid) {
    vector<vector<uint>> matrix(grid[0].size());

    vector<uint> row(grid.size());
    
}

size_t path(vector<vector<uint>>& grid, size_t& i, size_t& j) {

}

size_t score(vector<vector<uint>>& grid) {
    size_t total = 0, i, j;

    for (i = 0; i < grid.size(); i++) {
        for (j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 0) {
                total += path(grid, i, j);
            }
        }
    }


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
    vector<vector<uint>> grid;

    while (getline(file, line)) {
        vector<uint> nums;

        for (size_t i = 0; i < line.size(); i++) {
            nums.push_back(line[i] - '0');
        }
        grid.push_back(nums);
    }

    //cout <<  << endl;
    return 0;
}
