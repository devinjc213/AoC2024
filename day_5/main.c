#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_empty(const char *s)
{
    while ( isspace(*s) && s++ );
    return !*s;
}

typedef struct {
    int key;
    int value[100];
    int count;
} Map;

void init_map(Map *rules[500]) {
    for (int i = 0; i < 500; i++) {
        rules[i] = malloc(sizeof(Map));
    }
}

int get_index(Map *rules[500], int key) {
    for (int i = 0; i < 500; i++) {
        if (rules[i] != NULL && rules[i]->key == key) {
            return i;
        }
    }

    return -1;
}

void add_key(Map *rules[500], int key, int count) {
    rules[count]->key = key;
}

void add_value(Map *rules[500], int index, int value) {
    rules[index]->value[++rules[index]->count] = value;
}

int get_update_index(int update[25], int value, int count) {
    for (int i = 0; i < count; i++) {
        if (update[i] && update[i] == value) return i;
    }

    return -1;
}

int check_line(Map *rules[500], int update[25], int count) {
    int fail = 0;

    for (int i = 0; i < count && fail != 1; i++) {
        printf("\n\ncur i: %d", i);
        int rule_index = get_index(rules, update[i]);

        if (rule_index == -1) {
            continue;
        } else {
            printf("\nkey: %d", update[i]);
            printf("\ncount: %d", count);
            int key_update_index = get_update_index(update, rules[rule_index]->key, count);
            printf("\n key update index: %d", key_update_index);

            for (int j = 0; j < rules[rule_index]->count; j++) {
                int rule_value_index = get_update_index(update, rules[rule_index]->value[j], count);

                if (rule_value_index != -1) {
                    if (key_update_index > rule_value_index) {
                        fail = 1;
                        break;
                    }
                }
            }

        }
    }

    if (fail == 0) {
        return update[count / 2];
    }

    return 0;
}

int main() {
    FILE* input = fopen("input", "r");
    int count = 0;
    int total = 0;
    char line[255] = {0};

    Map *rules[500] = {0};
    init_map(rules);

    char *token;

    int line_break = 0;

    if (input != NULL) {
        while (fgets(line, sizeof(line), input)) {
            if (line_break == 0) {
                if (is_empty(line)) {
                    line_break = 1;
                    continue;
                }

                char s_key[3];
                char s_value[3];

                strncpy(s_key, line, 2);
                s_key[2] = '\0';
                strncpy(s_value, &line[3], 2);
                s_value[2] = '\0';

                int key, value;

                key = atoi(s_key);
                value = atoi(s_value);

                if (get_index(rules, key) == -1) {
                    add_key(rules, key, count);
                    add_value(rules, count, value);
                    count++;
                } else {
                    int index = get_index(rules, key);
                    add_value(rules, index, value);
                }            
            } else {
                int update[25] = {0};
                int token_count = 0;

                token = strtok(line, ","); 
                while (token != NULL) {
                    int num = atoi(token);
                    update[token_count++] = num;

                    token = strtok(NULL, ",");
                }

                total += check_line(rules, update, token_count);
            }

        }
    }

    printf("\n\nTotal: %d\n", total);
}
