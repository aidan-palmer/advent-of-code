#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fptr;
    char line[100];
    fptr = fopen("input.txt", "r");
    int sum = 0;

    if (fptr == NULL) {
        printf("Error: file not found.");
        return 0;
    }
    while (fgets(line, 100, fptr)) {

        int x = -1;
        int y = -1, i;
        for (i = 0; line[i] != '\0'; i++) {
            char c = line[i];

            if (c >= '0' && c <= '9') {
                if (x == -1) {
                    x = c - '0';
                } else {
                    y = c - '0';
                }
            }
        }

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