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

ulong quadrants(int grid[HEIGHT][WIDTH]) {
    ulong product = 1;
    uint q_sum = 0;
    int i, j;

    // top left
    for (i = 0; i < HEIGHT / 2; i++) {
        for (j = 0; j < WIDTH / 2; j++) {
            q_sum += grid[i][j];
        }
    }
    product *= q_sum;
    q_sum = 0;

    // top right
    for (i = 0; i < HEIGHT / 2; i++) {
        for (j = WIDTH / 2 + 1; j < WIDTH; j++) {
            q_sum += grid[i][j];
        }
    }
    product *= q_sum;
    q_sum = 0;

    // bottom left
    for (i = HEIGHT / 2 + 1; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH / 2; j++) {
            q_sum += grid[i][j];
        }
    }
    product *= q_sum; 
    q_sum = 0;

    // bottom right
    for (i = HEIGHT / 2 + 1; i < HEIGHT; i++) {
        for (j = WIDTH / 2 + 1; j < WIDTH; j++) {
            q_sum += grid[i][j];
        }
    }
    product *= q_sum;
    return product;
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

    for (int i = 0; i < 100; i++) {
        second(bots);
    }
    int sim[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            sim[i][j] = 0;
        }
    }

    for (robot r : bots) {
        sim[r.pos_y][r.pos_x]++;
    }

    cout << quadrants(sim) << endl;
    return 0;
}