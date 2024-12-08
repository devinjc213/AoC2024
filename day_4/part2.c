#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 140

int check(char array[LENGTH][LENGTH], int row, int column) {
    if (row > 0 && row < 139 && column > 0 && column < 139) {
        if (array[row-1][column-1] == 'M' && array[row+1][column-1] == 'M' && array[row-1][column+1] == 'S' && array[row+1][column+1] == 'S'){
            return 1;
        } else if (array[row-1][column-1] == 'S' && array[row+1][column-1] == 'S' && array[row-1][column+1] == 'M' && array[row+1][column+1] == 'M'){
            return 1;
        } else if (array[row-1][column-1] == 'M' && array[row-1][column+1] == 'M' && array[row+1][column-1] == 'S' && array[row+1][column+1] == 'S') {
            return 1;
        } else if (array[row-1][column-1] == 'S' && array[row-1][column+1] == 'S' && array[row+1][column-1] == 'M' && array[row+1][column+1] == 'M') {
            return 1;
        }
    }

    return 0;
}

int main() {
    char array[LENGTH][LENGTH] = {0};
    int row = 0;
    char line[145];
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
            if (array[i][j] == 'A') {
                xmas_count += check(array, i, j);
            }
        }
    }

    printf("%d", xmas_count);
}
