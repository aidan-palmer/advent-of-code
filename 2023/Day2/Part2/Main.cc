#include <bits/stdc++.h>

using namespace std;

int index_of(string s, char c) {
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            return i;
        }
    }
    return -1;
}

// 0 = red, 1 = green, 2 = blue
int color(string s) {
    smatch match;
    regex pattern("[A-Za-z]+");
    string col;
    while (regex_search(s, match, pattern)) {
        col = match.str(0);
        s = match.suffix().str();
    }
    if (col == "red") {
        return 0;
    } else if (col == "green") {
        return 1;
    } else {
        return 2;
    }
}

int quant(string s) {
    smatch match;
    regex pattern("\\d+");
    string num;
    while (regex_search(s, match, pattern)) {
        num = match.str(0);
        s = match.suffix().str();
    }
    return stoi(num);
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
    string cube;
    int total = 0;
    while (getline(file, line)) {
        line = line.substr(index_of(line, ':'));
        stringstream stream(line);
        int m_red = 0;
        int m_green = 0;
        int m_blue = 0;
        while (getline(stream, token, ';')) {
            int red = 0;
            int green = 0;
            int blue = 0;
            stringstream set(token);
            while (getline(set, cube, ',')) {
                int num = quant(cube);
                int col = color(cube);
                switch (col) {
                    case 0:
                        red += num;
                        break;
                    case 1:
                        green += num;
                        break;
                    case 2:
                        blue += num;
                        break;
                }
            }
            if (red > m_red) {
                m_red = red;
            }
            if (green > m_green) {
                m_green = green;
            }
            if (blue > m_blue) {
                m_blue = blue;
            }
        }
        total += m_red * m_green * m_blue;
    }
    cout << total << endl;
    return 0;
}
