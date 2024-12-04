#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int xmas(const vector<string>& words) {
    int total = 0;
    int i, j;

    for (i = 0; i < words.size(); i++) {
	for (j = 0; j < words[i].size(); j++) {
	    string right, down, diag;
	    try {
		right = words[i].substr(j, 4);
	    } catch (const out_of_range& e) {}
	    
            try {
		down = words[i].substr(j, 4);
	    } catch (const out_of_range& e) {}

	     try {
                diag = words[i].substr(j, 4);
            } catch (const out_of_range& e) {}
	    if (right == "XMAS" || right == "SAMX") {
		total++;
	    }
            if (down == "XMAS" || down == "SAMX") {
                total++;
            }
            if (diag == "XMAS" || diag == "SAMX") {
                total++;
            }
	}
    }
    return total;
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
    vector<string> words;

    while (getline(file, line)) {
        words.push_back(line);
    }
    cout << xmas(words) << endl;
    return 0;
}
