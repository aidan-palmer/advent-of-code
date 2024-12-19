#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <cmath>

using namespace std;

enum opcodes {
    adv = 0,
    bxl,
    bst,
    jnz,
    bxc,
    out,
    bdv,
    cdv
};

enum registers {
    A = 0,
    B,
    C
};

long reg[3];

int combo(int op) {
    if (op > 3) {
        return reg[op % 4];
    }
    return op % 4;
}

vector<int> run(const vector<int>& instr) {
    vector<int> output;
    int pc = 0;

    while (pc < int(instr.size())) {

        switch (instr[pc]) {
            case adv:
            {
                reg[A] /= pow(2, combo(instr[pc + 1]));
                pc += 2;
                break;
            }
            case bxl:
            {
                reg[B] ^= instr[pc + 1];
                pc += 2;
                break;
            }
            case bst:
            {
                reg[B] = combo(instr[pc + 1]) % 8;
                pc += 2;
                break;
            }
            case jnz:
            {
                if (reg[A] != 0) {
                    pc = instr[pc + 1];
                } else {
                    pc += 2;
                }
                break;
            }
            case bxc:
            {
                reg[B] ^= reg[C];
                pc += 2;
                break;
            }
            case out:
            {
                output.push_back(combo(instr[pc + 1]) % 8);
                pc += 2;
                break;
            }
            case bdv:
            {
                reg[B] = reg[A] / pow(2, combo(instr[pc + 1]));
                pc += 2;
                break;
            }
            case cdv:
            {
                reg[C] = reg[A] / pow(2, combo(instr[pc + 1]));
                pc += 2;
                break;              
            }
        }
    }
    return output;
}

bool equals(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) {
        return false;
    }

    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
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

    vector<int> instr;
    bool is_reg = true;

    while (getline(file, line)) {
        if (line.empty()) {
            is_reg = false;
            continue;
        }
        if (!is_reg) {
            stringstream stream(line.substr(9));

            while (getline(stream, token, ',')) {
                instr.push_back(stoi(token));
            }
        }
    }
    file.close();

    // answer is greater than int max

    for (long i = INT32_MAX; i < INT64_MAX; i++) {
        if (i % 8 == 0) {
            //cout << i << endl;
            reg[A] = i;
            reg[B] = 0;
            reg[C] = 0;
            vector<int> result = run(instr);

            if (equals(result, instr)) {
                cout << i << endl;
                return 0;
            }
        }

    }
    return 0;
}