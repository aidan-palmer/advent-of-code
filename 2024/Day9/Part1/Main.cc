#include <fstream>
#include <iostream>
#include <vector>

#define SPACE 255

using namespace std;

vector<uint8_t> expand(vector<uint8_t> nums) {
    vector<uint8_t> files;

    for (size_t i = 0, j = 0; i < nums.size(); i += 2, j++) {
        // Add ID number
        for (size_t k = 0; k < nums[i]; k++) {
            files.push_back(j);
        }
        // Add spaces
        for (size_t l = 0; l < nums[i + 1]; l++) {
            files.push_back(SPACE);
        }
    }
    return files;
}

vector<uint8_t> compact(vector<uint8_t> nums, size_t og_size) {
    size_t i = 1, j = nums.size() - 1;

    while (nums.size() > og_size) {
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

long checksum(const vector<uint8_t>& blocks) {
    long answer = 0;

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
    vector<uint8_t> nums;

    while (getline(file, line)) {
        for (size_t i = 0; i < line.size(); i++) {
            nums.push_back(line[i] - '0');
        }
    }

    cout << checksum(compact(expand(nums), nums.size())) << endl;
    return 0;
}
