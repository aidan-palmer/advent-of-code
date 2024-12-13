#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>

#define SPACE 255

using namespace std;

vector<uint8_t> expand(vector<uint8_t> nums) { 
    vector<uint8_t> files;

    for (size_t i = 0, j = 0; i < nums.size(); i += 2, j++) {
        // Add ID number
        for (size_t k = 0; k < nums[i]; k++) {
            files.push_back(uint8_t(j));
        }
        // Add spaces
        if (i < nums.size() - 1) {
            for (size_t l = 0; l < nums[i + 1]; l++) {
                files.push_back(SPACE);
            }
        }

    }
    cout << "Expanded size: " << files.size() << endl;
    return files;
}

vector<uint8_t> compact(vector<uint8_t> blocks) {
    vector<uint8_t> nums(blocks);
    size_t i = 1, j = nums.size() - 1;
/*
    // debugging
    for (size_t k = 0; k < 50; k++) {
        cout << int(nums[k]) << " ";
    }
    cout << endl << endl;*/

    while (i < j) {
        if (nums[i] == SPACE) {
            while (nums[j] == SPACE) {
                nums.pop_back();
                j--;
            }
            nums[i] = nums[j];
            nums.pop_back();
            j--;
/*
            // debugging
            for (size_t k = 0; k < nums.size(); k++) {
                cout << int(nums[k]) << " ";
            }
            cout << endl << endl;*/
        }
        i++;
    }
    return nums;
}

size_t checksum(const vector<uint8_t>& blocks) {
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
    vector<uint8_t> nums;
    size_t count = 0;

    while (getline(file, line)) {
        for (size_t i = 0; i < line.size(); i++) {
            nums.push_back(uint8_t(line[i] - '0'));
            count++;
        }
    }
    cout << "Input length: " << count << endl;

    cout << checksum(compact(expand(nums))) << endl;
    return 0;
}
