#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;



pair<int, int> brute_force(vector<int> original) {
    for (size_t j = 0; j < 100; j++) {
        for (size_t k = 0; k < 100; k++) {
            vector<int> intcode = original;
            intcode[1] = j;
            intcode[2] = k;
            bool halt = false;

            for (size_t i = 0; i < intcode.size(); i += 4) {
            /*    if (intcode[0] == 19690720) {
                    return make_pair(j, k);
                }*/
                switch (intcode[i]) {
                    case 1:
                    {
                        intcode[intcode[i + 3]] = intcode[intcode[i + 1]] + intcode[intcode[i + 2]];
                        break;
                    }
                    case 2:
                    {
                        intcode[intcode[i + 3]] = intcode[intcode[i + 1]] * intcode[intcode[i + 2]];
                        break;              
                    }
                    case 99:
                    {
                        halt = true;
                        break;
                    }
                }
                if (halt) {
                    break;
                }
            }
            //cout << intcode[0] << endl;
            if (intcode[0] == 19690720) {
                return make_pair(j, k);
            }
        }
    }
    return make_pair(-1, -1);
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
    vector<int> intcode;
    //int total = 0;

    while (getline(file, line)) {
        stringstream stream(line);

        while (getline(stream, token, ',')) {
            intcode.push_back(stoi(token));
        }
    }

    pair<int, int> brute = brute_force(intcode);

    cout << 100 * brute.first + brute.second << endl;
    return 0;
}