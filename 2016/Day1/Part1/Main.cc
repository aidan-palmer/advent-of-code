#include <bits/stdc++.h>

using namespace std;

/*
North = 0
East = 1
South = 2
West = 3
*/

void turn_right(int& dir) {
    if (dir == 3) {
        dir = 0;
    } else {
        dir++;
    }
}

void turn_left(int& dir) {
    if (dir == 0) {
        dir = 3;
    } else {
        dir--;
    }
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
    int dir = 0;
    int x = 0;
    int y = 0;

    while (getline(file, line)) {
        stringstream stream(line);
        while (getline(stream, token, ' ')) {
            if (!token.empty()) {
                char turn = token[0];
                size_t comma_index = token.find(',');
                string num;
                if (comma_index == string::npos) {
                    num = token.substr(1);
                } else {
                    num = token.substr(1, comma_index - 1);
                }
                int dist = stoi(num);
                if (turn == 'R') {
                    turn_right(dir);
                } else {
                    turn_left(dir);
                }
                switch(dir) {
                    case 0:
                    {
                        y += dist;
                        break;
                    }
                    case 1:
                    {
                        x += dist;
                        break;
                    }
                    case 2:
                    {
                        y -= dist;
                        break;
                    }
                    case 3:
                    {
                        x -= dist;
                        break;
                    }
                }

            }
            
        }
    }
    int blocks_away = abs(x) + abs(y);
    cout << blocks_away << endl;
    return 0;
}