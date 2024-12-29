#include <iostream>
#include <algorithm>

using namespace std;

#define LOWER 197487
#define UPPER 673251

bool same_digit(int num) {
    string s = to_string(num);
    size_t i;

    for (i = 0; i < s.size() - 2; i++) {
        if (s[i] == s[i + 1] && s[i] != s[i + 2]) {
            return true;
        }
    }
    if (s[i] == s[i + 1] && s[i] != s[i - 1]) {
        return true;
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
   // int total = 0, i;
   cout << same_digit(112233) << " " << not_decrease(112233) << endl; // true
   cout << same_digit(123444) << " " << not_decrease(123444) << endl; // false
   cout << same_digit(111122) << " " << not_decrease(111122) << endl; // true
/*
    for (i = LOWER + 1; i < UPPER; i++) {
        if (same_digit(i) && not_decrease(i)) {
            total++;
        }
    }

    cout << total << endl;*/
    return 0;
}