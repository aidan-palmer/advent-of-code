#include <bits/stdc++.h>

using namespace std;


string parse_checksum(string line) {
    size_t bracket_index = line.find('[');
    return line.substr(bracket_index + 1, 5);
}

int parse_sector_id(string line) {
    size_t last_dash = line.rfind('-');
    size_t bracket_index = line.find('[');
    string num = line.substr(last_dash + 1, bracket_index - last_dash - 1);
    return stoi(num);
}

string parse_encrypted_name(string line) {
    size_t last_dash = line.rfind('-');
    string sub = line.substr(0, last_dash);
    erase(sub, '-');
    return sub;
}

bool is_real(string& e_name, string& checksum) {
    map<char, int> common;
    for (const char& c : e_name) {
        common[c]++;
    }
    string sorted = "";
    int i;

    for (const auto& m : common) {
        if (!sorted.empty()) {
            int insert_index = 0;
            int n = sorted.size();

            for (i = n - 1; i >= 0; i--) {
                if (common[sorted[i]] >= m.second) {
                    insert_index = i + 1;
                    break;
                }
            }
            sorted.insert(sorted.begin() + insert_index, m.first);
        } else {
            sorted.push_back(m.first);
        }
    }
    return sorted.substr(0, 5) == checksum;
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
    int sum = 0;

    while (getline(file, line)) {
        string checksum = parse_checksum(line);
        string e_name = parse_encrypted_name(line);

        if (is_real(e_name, checksum)) {
            int sector_id = parse_sector_id(line);
            sum += sector_id;
        }
    }
    cout << sum << endl;
    return 0;
}