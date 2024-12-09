#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int test_line(int test_val, int array[15], int count) {
    uint32_t total_combinations = 1U << count;


    for (int i = 0; i < total_combinations; i++) {
        uint32_t temp_total = array[0];
        for (int j = 0; j < count; j++) {
            if (i & (1U << (j - 1))) {
                temp_total += array[j] ;
            } else {
                temp_total *= array[j];
            }
        }

        if (temp_total == test_val) return test_val;
    }

    return 0;
}

int main() {
    FILE* input = fopen("input", "r");
    char *token;
    char line[128];
    int total = 0;

    int possible_total = 0;

    if (input != NULL) {
        while (fgets(line, sizeof(line), input)) {
            token = strtok(line, ":");
            int test_val;
            int array[15];
            int count = 0;
            
            if (token != NULL) {
                test_val = atoi(token);

                possible_total += test_val;

                token = strtok(NULL, " ");

                while (token != NULL) {
                    int testable_val = atoi(token);

                    array[count++] = testable_val;

                    token = strtok(NULL, " ");
                }
            }

            total += test_line(test_val, array, count);
        }
    }

    printf("possible total: %d", possible_total);
    printf("total: %d", total);
}
