#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//TODO debug. Wrong answer.
int compare_string(int length, char str1[], char str2[]) { // Returns boolean int
    int i;

    for (i = 0; i < length; i++) {
        if (str1[i] != str2[i]) {
            return 0;
        }
    }
    return 1;
}

int string_to_int(int length, char str[]) {
    if (length == 3) {
        if (compare_string(length, str, "one")) {
            return 1;
        } else if (compare_string(length, str, "two")) {
            return 2;
        } else if (compare_string(length, str, "six")) {
            return 6;
        } else {
            return -1;
        }
    } else if (length == 4) {
        if (compare_string(length, str, "four")) {
            return 4;
        } else if (compare_string(length, str, "five")) {
            return 5;
        } else if (compare_string(length, str, "nine")) {
            return 9;
        } else {
            return -1;
        }
    } else if (length == 5) {
        if (compare_string(length, str, "three")) {
            return 3;
        } else if (compare_string(length, str, "seven")) {
            return 7;
        } else if (compare_string(length, str, "eight")) {
            return 8;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
} 
     

int main() {

    //char test[] = "three";
    //char test2[] = "four";
    //printf("%d", string_to_int(5, test));

    FILE *fptr;
    char line[100];
    fptr = fopen("part2input.txt", "r");
    int sum = 0;

    if (fptr == NULL) {
        printf("Error: file not found.");
        return 0;
    }
    while (fgets(line, 100, fptr)) {
        //printf("%s", line);
        //int s = sizeof(line) / sizeof(line[0]);
        //printf("%d\n", s);
        char alpha[50];
        int j = 0; //alpha running index
        // || line[i] != '\n'

        int x = -1;
        int y = -1, i;
        for (i = 0; line[i] != '\0' && line[i] != '\n'; i++) {
            char c = line[i];
            //printf("%c", c);
            //printf("%d ", i);

            if (c >= '0' && c <= '9') {
                if (x == -1) {
                    x = c - '0';
                } else {
                    y = c - '0';
                }
                if (j > 0) {
                    //memset(alpha, '\0', sizeof(alpha));
                    j = 0;
                }
                

            } else {
                alpha[j] = c;
                j++;
                int z = string_to_int(j, alpha);
                if (z != -1) {
                    if (x == -1) {
                        x = z;
                    } else {
                        y = z;
                    }
                    j = 0;
                }


            }
        }
       // printf("\n");
        //printf("%d %d", x, y);

        if (y == -1) {
            sum += x * 10 + x;
        } else {
            sum += x * 10 + y;
        }
    }
    printf("%d", sum);

    fclose(fptr);

    return 0;
}