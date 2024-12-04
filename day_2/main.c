#define LINES 1000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// increasing or decreasing
// 1 < abs(a - b) >= 3!
//
// Thanks stack overflow
int is_empty(const char *s)
{
    while ( isspace(*s) && s++ );
    return !*s;
}

int is_out_of_bounds(int last_val, int val) {
    if (abs(last_val - val) > 3 || abs(last_val - val) < 1) {
        return 1;
    }

    return 0;
}

//return 1 for incrementing 
//-1 for decreasing
int is_incrementing(int last_val, int val) {
    if (last_val - val > 0) return -1;
    else if (last_val - val == 0) return 0;
    else return 1;
}

int should_skip(int incrementing, int last_val, int val) {
    if (incrementing == -1 && last_val - val < 0) {
        return 1;
    }
    else if (incrementing == 1 && last_val - val > 0) {
        return 1;
    }

    return 0;
}

int main() {
    FILE* input = fopen("input", "r");
    char line[24];

    int safe_count = 0;
    int line_count = 0;

    if (input != NULL) {
        while (fgets(line, sizeof(line), input)) {
            if (is_empty(line)) continue;
            char *token;
            int skip = 0;
            int oob_skip = 0;
            int incrementing = 0;

            int last_val = 0;
            int token_index = 0;
            int token_length = 0;
            token = strtok(line, " ");

            int increment_count = 0;
            int decrement_count = 0;
            int dupe_count = 0;

            printf("\ntoken:\n");
            while (token != NULL) {
                printf("%s ", token);
                int val = atoi(token); 

                if (last_val != 0) {
                    if (is_out_of_bounds(last_val, val)) {
                        oob_skip += 1;
                    }

                    if (is_incrementing(last_val, val) > 0) {
                        increment_count++;
                    } else if (is_incrementing(last_val, val) < 0) {
                        decrement_count++;
                    }
                }

                last_val = val;
                token_index++;
                token = strtok(NULL, " ");
            }
            token_length = token_index;

            printf("\n token length: %d\n increment_count: %d\n decrement_count: %d\n oob_skip: %d\n", token_length, increment_count, decrement_count, oob_skip);

            if (oob_skip <= 2 && (increment_count == token_length - 1 || decrement_count == token_length - 1)) {
                safe_count++;
                printf("IS SAFE\n\n");
            } else if (oob_skip == 0 && (token_length - increment_count <= 2 || token_length - decrement_count <= 2 || token_length - increment_count + decrement_count == token_length - 1)) {
                safe_count++;
                printf("IS SAFE\n\n");
            } else if (oob_skip == 1) {
                if (increment_count > decrement_count && increment_count + oob_skip == token_length - 1) {
                    safe_count++;
                    printf("IS SAFE\n\n");
                } else if (increment_count < decrement_count && decrement_count + oob_skip == token_length - 1) {
                    safe_count++;
                    printf("IS SAFE\n\n");
                }

            } else {
                printf("IS NOT SAFE :(\n\n");
            }

            oob_skip = 0;
            last_val = 0;
            token_index = 0;
            token_length = 0;
            increment_count = 0;
            decrement_count = 0;

            line_count++;
        }

    }

    printf("\n\n%d", safe_count);
}
