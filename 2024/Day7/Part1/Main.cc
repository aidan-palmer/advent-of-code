#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>

using namespace std;

void permutations(vector<string>& result, string current, size_t size) {
    if (current.size() == size) {
        result.push_back(current);
        return;
    }
    permutations(result, current + "+", size);
    permutations(result, current + "*", size);
}

vector<string> permute(int size) {
    vector<string> result;
    permutations(result, "", size);
    return result;
}

bool is_valid(stack<long>& nums, long& test_val) {
    vector<string> per = permute(nums.size() - 1);

    for (size_t i = 0; i < per.size(); i++) {
        stack<long> copy(nums);
        long val = copy.top();
        copy.pop();

        for (size_t j = 0; j < per[i].size(); j++) {
            long cur = copy.top();
            copy.pop();

            if (per[i][j] == '*') {
                val *= cur;
            } else {
                val += cur;
            }
        }
        if (val == test_val) {
            return true;
        }
    }
    return false;
}

long calibrate(const vector<vector<long>>& equations) {
    long total = 0;
    size_t i, j;

    for (i = 0; i < equations.size(); i++) {
        long test_value = equations[i][0];
        stack<long> nums;

        for (j = equations[i].size() - 1; j > 0; j--) {
            nums.push(equations[i][j]);
        }
        if (is_valid(nums, test_value)) {
            total += test_value;
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
    string token;
    vector<vector<long>> equations;

    while (getline(file, line)) {
        vector<long> equation;
        string num;
        size_t i = 0;

        while (line[i] != ':') {
            num += line[i];
            i++;
        }
        try {
            equation.push_back(stol(num));
        } catch (const invalid_argument& e) {
            cout << "Error: Could not parse " << num << endl;
            return 3;
        }
        stringstream stream(line.substr(i + 2));

        try {
            while (getline(stream, token, ' ')) {
                equation.push_back(stol(token));
            }
        } catch (const invalid_argument& e) {
            cout << "Error: Could not parse " << token << endl;
            return 4;
        }
        equations.push_back(equation);
    }

    cout << calibrate(equations) << endl;
    return 0;
}
