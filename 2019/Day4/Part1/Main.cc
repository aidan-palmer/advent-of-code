#include <iostream>
#include <algorithm>

using namespace std;

#define LOWER 197487
#define UPPER 673251

bool same_digit(int num) {
    string s = to_string(num);

    for (size_t i = 0; i < s.size() - 1; i++) {
        if (s[i] == s[i + 1]) {
            return true;
        }
    }
    return false;
}

bool not_decrease(int num) {
    string s = to_string(num);
    string sorted = s;
    sort(sorted.begin(), sorted.end());

    return s == sorted;
}

int main(void) {
    int total = 0, i;

    for (i = LOWER + 1; i < UPPER; i++) {
        if (same_digit(i) && not_decrease(i)) {
            total++;
        }
    }

    cout << total << endl;
    return 0;
}