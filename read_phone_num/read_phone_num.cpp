#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <unistd.h>

using namespace std;

const char *digits[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const char *successive[] = {NULL, NULL, "double", "triple", "quadruple", "quintuple", "sextuple", "septuple", "octuple", "nonuple", "decuple"};

struct token {
    char *start;
    int len;
};

void read_one_token(char *pos, int len) {
    char *cur = pos + 1;
    char suc_char = *pos;
    int suc_count = 1;

    while (cur != pos + len) {
        if (*cur == suc_char) {
            suc_count++;
        } else {
            if (suc_count > 1 && suc_count < 11)
                printf("%s %s ", successive[suc_count], digits[suc_char - '0']);
            else {
                int i;
                for (i = 0; i < suc_count; i++)
                    printf("%s ", digits[suc_char - '0']);
            }
            suc_char = *cur;
            suc_count = 1;
        }
        cur++;
    }
    if (suc_count > 1 && suc_count < 11)
        printf("%s %s ", successive[suc_count], digits[suc_char - '0']);
    else {
        int i;
        for (i = 0; i < suc_count; i++)
            printf("%s ", digits[suc_char - '0']);
    }
    return;
}

int main(int argc, char **argv) {
    int total_cases = 0;
    int cur_case = 0;
    char *input_buf = NULL;
    size_t input_size = 0;
    
    getline(&input_buf, &input_size, stdin);
    total_cases = atoi(input_buf);
    free(input_buf);
    input_buf = NULL;

    while (cur_case < total_cases) {
        vector<struct token> tokens;
        vector<struct token>::iterator it;
        char *cur_pos = NULL;
        char *parse_pos = NULL;
        int cur_len = 0;
        struct token cur;

        getline(&input_buf, &input_size, stdin);
        parse_pos = strchr(input_buf, ' ') + 1;
        parse_pos = strtok(parse_pos, "-");
        cur.len = atoi(parse_pos);
        cur.start = input_buf;
        tokens.push_back(cur);

        while ((parse_pos = strtok(NULL, "-")) != NULL) {
            cur.start = cur.start + cur.len;
            cur.len = atoi(parse_pos);
            tokens.push_back(cur);
        }

        printf("Case #%d: ", cur_case + 1);
        for (it = tokens.begin(); it != tokens.end(); it++) {
            //printf("%.*s\n", it->len, it->start);
            read_one_token(it->start, it->len);
        }
        printf("\n");

        free(input_buf);
        input_buf = NULL;
        cur_case++;
    }

    return 0;
}

