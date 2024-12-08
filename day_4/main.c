#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 140

int check(char array[LENGTH][LENGTH], char match[4], int row, int column, int letter, int dx, int dy) {
    if (match[letter] == 'S' && array[row][column] == match[letter]) {
        return 1;
    } else if (0 <= row + dx && row + dx <= LENGTH - 1 &&
               0 <= column + dy && column + dy <= LENGTH - 1 &&
               array[row + dx][column + dy] == match[letter + 1]) {

        return check(array, match, row + dx, column + dy, letter + 1, dx, dy);
    }

    return 0;
}

int main() {
    char array[LENGTH][LENGTH] = {0};
    int row = 0;
    char line[145];
    char match[4] = "XMAS";
    int xmas_count;

    FILE* input = fopen("input", "r");

    if (input != NULL) {
        while (fgets(line, sizeof(line), input)) {
            for (int i = 0; i < LENGTH; i++) {
                if (line[i] == 'X' || line[i] == 'M' || line[i] == 'A' || line[i] == 'S') {
                    array[row][i] = line[i];
                }
            }

            row++;
        }
    }

    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if (array[i][j] == 'X') {
                xmas_count += check(array, match, i, j, 0, 1, 0);
                xmas_count += check(array, match, i, j, 0, -1, 0);
                xmas_count += check(array, match, i, j, 0, 0, 1);
                xmas_count += check(array, match, i, j, 0, 0, -1);

                xmas_count += check(array, match, i, j, 0, 1, 1);
                xmas_count += check(array, match, i, j, 0, -1, -1);
                xmas_count += check(array, match, i, j, 0, -1, 1);
                xmas_count += check(array, match, i, j, 0, 1, -1);
            }
        }
    }

    printf("%d", xmas_count);
}
