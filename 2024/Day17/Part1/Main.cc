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

vector<int> reg;

int combo(uint8_t op) {
    if (op > 3) {
        return reg[op % 4];
    }
    return op % 4;
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
        if (is_reg) {
            reg.push_back(stoi(line.substr(12)));
        } else {
            stringstream stream(line.substr(9));

            while (getline(stream, token, ',')) {
                instr.push_back(stoi(token));
            }
        }
    }
    file.close();

    int pc = 0;
    vector<int> output;

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
    size_t i;

    for (i = 0; i < output.size() - 1; i++) {
        cout << output[i] << ",";
    }
    cout << output[i] << endl;

    return 0;
}