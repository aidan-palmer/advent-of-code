#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <cstdint>

using namespace std;

#define ACOST 3
#define BCOST 1

struct prize {
    uint btn_a_x, btn_a_y, btn_b_x, btn_b_y, prize_x, prize_y;
};

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

    while (getline(file, line)) {
        stringstream stream(line);

        

        
    }
    /*
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int total = 0;
*/

    //cout << total << endl;
    return 0;
}