#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>

#define SPACE (UINT32_MAX)

using namespace std;

vector<size_t> expand(vector<size_t> nums) { 
    vector<size_t> files;

    for (size_t i = 0, j = 0; i < nums.size(); i += 2, j++) {
        // Add ID number
        for (size_t k = 0; k < nums[i]; k++) {
            files.push_back(size_t(j));
        }
        // Add spaces
        if (i < nums.size() - 1) {
            for (size_t l = 0; l < nums[i + 1]; l++) {
                files.push_back(SPACE);
            }
        }
    }
    return files;
}

vector<size_t> compact(vector<size_t> blocks) {
    vector<size_t> nums(blocks);
    size_t i = 1, j = nums.size() - 1;

    while (i < j) {
        if (nums[i] == SPACE) {
            while (nums[j] == SPACE) {
                nums.pop_back();
                j--;
            }
            nums[i] = nums[j];
            nums.pop_back();
            j--;
        }
        i++;
    }
    return nums;
}

size_t checksum(const vector<size_t>& blocks) {
    size_t answer = 0;

    for (size_t i = 1; i < blocks.size(); i++) {
        answer += i * blocks[i];
    }
    return answer;
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
    vector<size_t> nums;

    while (getline(file, line)) {
        for (size_t i = 0; i < line.size(); i++) {
            nums.push_back(line[i] - '0');
        }
    }

    cout << checksum(compact(expand(nums))) << endl;
    return 0;
}
