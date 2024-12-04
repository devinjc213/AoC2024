#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

size_t closest(size_t cur, size_t pos[100], int count) {
    for (int i = 0; i < count; i++) {
        if (i == count) return pos[i];
        if (pos[i] < cur && cur < pos[i+1]) {
            return pos[i];
        }
    }

    return 0;
}

int main() {
    FILE* input = fopen("input", "r");
    int total = 0;
    int match_count = 0;
    int enabled = 1;
    int do_count = 0;
    size_t do_pos[100];
    int dont_count = 0;
    size_t dont_pos[100];

    char line[64000];
    regex_t regex, reg2, reg3;
    regmatch_t rm[3], rm2[1], rm3[1];
    char* pattern = "mul\\(([0-9]{1,3}),([0-9]{1,3})\\)";
    char* enable_pattern = "do\\(\\)";
    char* disable_pattern = "don't\\(\\)";

    if (input != NULL) {
        size_t total_read = fread(line, 1, sizeof(line) - 1, input);
        line[total_read] = '\0';

        int status = regcomp(&regex, pattern, REG_EXTENDED);
        int do_status = regcomp(&reg2, enable_pattern, REG_EXTENDED);
        int dont_status = regcomp(&reg3, disable_pattern, REG_EXTENDED);
        size_t base_offset = 0;
        size_t do_base_offset = 0;
        size_t dont_base_offset = 0;

        if (status != 0 || do_status != 0 || dont_status != 0) {
            printf("regex error compiling");
        }

        const char* search_ptr = line;
        const char* do_ptr = line;
        const char* dont_ptr = line;

        while(regexec(&reg2, do_ptr, 1, rm2, 0) == 0) {
            size_t match_pos = do_base_offset + rm2[0].rm_so;
            do_pos[do_count++] = match_pos;

            do_ptr += rm2[0].rm_eo;
            do_base_offset += rm2[0].rm_eo;
        }

        while(regexec(&reg3, dont_ptr, 1, rm3, 0) == 0) {
            size_t match_pos = dont_base_offset + rm3[0].rm_so;
            dont_pos[dont_count++] = match_pos;
            
            dont_ptr += rm3[0].rm_eo;
            dont_base_offset += rm3[0].rm_eo;
        }

        printf("%lu\n\n\n", do_pos[0]);
        printf("%lu\n\n\n", dont_pos[0]);

        while(regexec(&regex, search_ptr, 3, rm, 0) == 0) {
            size_t match_pos = base_offset + rm[0].rm_so;

            size_t closest_do;
            size_t closest_dont;

            if (match_pos >= dont_pos[0]) {
                closest_do = closest(match_pos, do_pos, do_count);
                closest_dont = closest(match_pos, dont_pos, dont_count);
            }

            printf("match pos: %lu\n", match_pos);
            printf("closest do: %lu\n", closest_do);
            printf("closest dont: %lu\n", closest_dont);

            if (match_pos < dont_pos[0] || closest_do > closest_dont) {
                match_count++;
                char full_match[32];
                int match_len = rm[0].rm_eo - rm[0].rm_so;
                strncpy(full_match, search_ptr + rm[0].rm_so, match_len);
                full_match[match_len] = '\0';

                char num1[5];
                char num2[5];

                int num1_len = rm[1].rm_eo - rm[1].rm_so;
                int num2_len = rm[2].rm_eo - rm[2].rm_so;

                strncpy(num1, search_ptr + rm[1].rm_so, num1_len);
                num1[num1_len] = '\0';
                strncpy(num2, search_ptr + rm[2].rm_so, num2_len);
                num2[num2_len] = '\0';

                int val1 = atoi(num1);
                int val2 = atoi(num2);

                total += val1 * val2;

                printf("Match %d\n", match_count);
                printf("Full match: %s\n", full_match);
                printf("sub match 1: %s\n", num1);
                printf("sub match 2: %s\n", num2);
                printf("Match start: %d\n Match end: %d\n", rm[0].rm_so, rm[0].rm_eo);
                printf("Sub match 1 start: %d\n Sub match 1 end: %d\n", rm[1].rm_so, rm[1].rm_eo);
                printf("Sub match 2 start: %d\n Sub match 2 end: %d\n", rm[2].rm_so, rm[2].rm_eo);
            }
            
            search_ptr += rm[0].rm_eo;
            base_offset += rm[0].rm_eo;

            printf("\n\n");
        }

    }

    printf("\n\n total matches: %d", match_count);
    printf("\n\n total count: %d", total);

    fclose(input);

    regfree(&regex);
}
