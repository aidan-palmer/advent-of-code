#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

vector<string> image;
vector<pair<long, long>> nodes; // indices of galaxy, identifier of galaxy
map<pair<pair<long, long>, pair<long, long>>, long> distances; // indices of two galaxies, path distance

bool empty_row(string s) {
    for (char c : s) {
        if (c == '#') {
            return false;
        }
    }
    return true;
}

bool empty_col(int j) {
    for (size_t i = 0; i < image.size(); i++) {
        if (image[i][j] == '#') {
            return false;
        }
    }
    return true;
}

void expand_rows(vector<int>& rows) {
    /*
    string empt(image[0].size(), '.');
    size_t times = 999'999;
    for (size_t r = 0; r < rows.size(); r++) {
        for (size_t j = 0; j < times; j++) { //
            image.insert(image.begin() + rows[r], empt);
        }
        for (size_t i = r + 1; i < rows.size(); i++) {
            rows[i] += times;
        }
    }*/
    size_t times = 99;
    for (size_t r = 0; r < rows.size(); r++) {
        for (size_t i = 0; i < nodes.size(); i++) {
            if (nodes[i].first > rows[r]) {
                nodes[i].first += times;
            }
        }
        for (size_t i = r + 1; i < rows.size(); i++) {
            rows[i] += times;
        }
    }
}

void expand_cols(vector<int> cols) {
    /*
    size_t times = 999'999;
    for (size_t c = 0; c < cols.size(); c++) {
        for (size_t k = 0; k < times; k++) {
            for (size_t i = 0; i < image.size(); i++) {
                image[i].insert(image[i].begin() + cols[c], '.');
            }
        }
        for (size_t j = c + 1; j < cols.size(); j++) {
            cols[j] += times;
        }
    }*/
    size_t times = 99;
    for (size_t c = 0; c < cols.size(); c++) {
        for (size_t i = 0; i < nodes.size(); i++) {
            if (nodes[i].second > cols[c]) {
                nodes[i].second += times;
            }
        }
        for (size_t i = c + 1; i < cols.size(); i++) {
            cols[i] += times;
        }
    }
}

void assign_id() {
    for (size_t i = 0; i < image.size(); i++) {
        for (size_t j = 0; j < image[i].size(); j++) {
            if (image[i][j] == '#') {
                nodes.push_back(make_pair(i, j));
            }
        }
    }
}

void find_lengths() {
    for (auto& p : nodes) {
        for (auto& r : nodes) {
            int dist = abs(p.first - r.first) + 
                abs(p.second - r.second);
            distances[make_pair(make_pair(p.first, r.first), make_pair(p.second, r.second))] = dist;
        }
    }
}

int sum() {
    int total = 0;
    for (const auto& p : distances) {
        if (p.first.first != p.first.second) {
            total += p.second;
        }
    }
    return total / 2;
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
    while (getline(file, line)) {
        for (size_t i = 0; i < line.size(); i++) {
        }
        image.push_back(line);
    }
    vector<int> rows;
    vector<int> cols; // to expand
    for (size_t i = 0; i < image.size(); i++) {
        if (empty_row(image[i])) {
            rows.push_back(i);
        }
    }
    for (size_t j = 0; j < image[0].size(); j++) {
        if (empty_col(j)) {
            cols.push_back(j);
        }
    }
    expand_rows(rows);
    expand_cols(cols);
    assign_id();
    find_lengths();
    int total = sum();
    cout << total << endl;
    return 0;
}