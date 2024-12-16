#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

#define WIDTH 101
#define HEIGHT 103

struct robot {
    int pos_x, pos_y, vel_x, vel_y;
};

void second(vector<robot>& bots) {
    for (size_t i = 0; i < bots.size(); i++) {
        if (bots[i].pos_x + bots[i].vel_x < 0) {
            bots[i].pos_x += bots[i].vel_x + WIDTH;
        } else {
            bots[i].pos_x = (bots[i].pos_x + bots[i].vel_x) % WIDTH;
        }
        if (bots[i].pos_y + bots[i].vel_y < 0) {
            bots[i].pos_y += bots[i].vel_y + HEIGHT;
        } else {
            bots[i].pos_y = (bots[i].pos_y + bots[i].vel_y) % HEIGHT;
        }
    }
}

// check if any row has at least 9 consecutive X's
bool sequence(char sim[HEIGHT][WIDTH]) {
    int j, k;

    for (j = 0; j < HEIGHT; j++) {
        int count = 0;
        for (k = 0; k < WIDTH - 1; k++) {
            if (sim[j][k] == 'X' && sim[j][k + 1] == 'X') {
                count++;
                if (count > 8) {
                    return true;
                }
            } else {
                count = 0;
            }
        }
    }
    return false;
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
    vector<robot> bots;
    int i, j, k;

    while (getline(file, line)) {
        robot r;
        size_t com1 = line.find(',');
        size_t com2 = line.find(',', com1 + 1);
        size_t v = line.find('v');
        r.pos_x = stoi(line.substr(2, com1 - 2));
        r.pos_y = stoi(line.substr(com1 + 1, (v - 1) - (com1 + 1)));
        r.vel_x = stoi(line.substr(v + 2, com2 - (v + 2)));
        r.vel_y = stoi(line.substr(com2 + 1));
        bots.push_back(r);
    }
    file.close();
    fstream out("output.txt");

    for (i = 1; i < 10000; i++) {
        second(bots);
        char sim[HEIGHT][WIDTH];

        for (j = 0; j < HEIGHT; j++) {
            for (k = 0; k < WIDTH; k++) {
                sim[j][k] = '.';
            }
        }
        for (robot r : bots) {
            sim[r.pos_y][r.pos_x] = 'X';
        }
        if (sequence(sim)) {
            for (j = 0; j < HEIGHT; j++) {
                for (k = 0; k < WIDTH; k++) {
                    out << sim[j][k];
                }
                out << "\n";
            }
            out << "\nSecond: " << i << "\n\n";
        }
    }
    out.close();
    return 0;
}