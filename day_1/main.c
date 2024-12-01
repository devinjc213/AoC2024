#define LINES 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main() {
    int list_1[LINES];
    int list_2[LINES];

    FILE* input = fopen("input", "r");

    char line[15];
    int count = 0;
    int distance = 0;

    if (input != NULL) {
        while (fgets(line, sizeof(line), input)) {
            char s_val_1[6];
            char s_val_2[6];

            strncpy(s_val_1, line, 5);
            s_val_1[5] = '\0';

            strncpy(s_val_2, line + 8, 5);
            s_val_2[5] = '\0';

            int val_1 = atoi(s_val_1);
            int val_2 = atoi(s_val_2);

            if (count < LINES) {
                list_1[count] = val_1;
                list_2[count] = val_2;
                count++;
            }
        }

        fclose(input);

        qsort(list_1, LINES, sizeof(int), compare);
        qsort(list_2, LINES, sizeof(int), compare);

        for (int i = 0; i < LINES; i++) {
            distance += abs(list_1[i] - list_2[i]);
        }

        printf("total distance: %d", distance);

        // PART 2
        int total = 0;

        for (int i = 0; i < LINES; i++) {
            int count = 0;

            for (int j = 0; j < LINES; j++) {
                if (list_1[i] == list_2[j]) {
                    count++;
                }
            }

            total += list_1[i] * count;
        }

        printf("total sim check: %d", total);

    } else {
        fprintf(stderr, "Unable to open file!\n");
    }

    return 0;
}
