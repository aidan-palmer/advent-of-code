#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <stdio.h>

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
                //cout << token << " ";
            }
        }
    }
    file.close();
    //cout << instr.size() << endl;
/*
    for (size_t i = 0; i < reg.size(); i++) {
        cout << reg[i] << " ";
    }
    cout << endl;

    for (size_t i = 0; i < instr.size(); i++) {
        cout << instr[i] << " ";
    }
    cout << endl;
*/
    int pc = 0;

    while (pc < int(instr.size())) {
        //cout << pc << endl;

        switch (instr[pc]) {
            case adv:
            {
                reg[A] /= pow(combo(instr[pc + 1]), 2);
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
                    //cout << "pc: " << pc << endl;
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
                cout << instr[pc + 1] % 8 << "," << endl;
                pc += 2;
                break;
            }
            case bdv:
            {
                reg[B] = reg[A] / pow(combo(instr[pc + 1]), 2);
                pc += 2;
                break;
            }
            case cdv:
            {
                reg[C] = reg[A] / pow(combo(instr[pc + 1]), 2);
                pc += 2;
                break;              
            }
        }
    }



    //cout <<  << endl;
    return 0;
}