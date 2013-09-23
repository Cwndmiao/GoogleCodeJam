#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct node {
    struct node *parent;
    struct node *child;
    unsigned long fenzi;
    unsigned long fenmu;
    unsigned long index;
    bool left;
};

void solve1(int cur, unsigned long arg1) {
    struct node *root_node = NULL;
    struct node *leaf_node = NULL;
    struct node *cur_node = (struct node*)malloc(sizeof(struct node));
    leaf_node = cur_node;
    cur_node->index = arg1;

    while (cur_node->index != 1) {
        struct node *par_node = (struct node*)malloc(sizeof(struct node));
        cur_node->parent = par_node;
        par_node->parent = NULL;
        par_node->child = cur_node;
        if (cur_node->index % 2) {
            par_node->left = false;
        } else {
            par_node->left = true;
        }
        par_node->index = cur_node->index / 2;
        cur_node = par_node;
    }
    root_node = cur_node;
    root_node->parent = NULL;
    root_node->fenzi = root_node->fenmu = 1;
    root_node->index = 1;

    cur_node = root_node->child;
    while (cur_node != leaf_node) {
        if (cur_node->parent->left) {
            cur_node->fenzi = cur_node->parent->fenzi;
            cur_node->fenmu = cur_node->parent->fenzi + cur_node->parent->fenmu;
        } else {
            cur_node->fenzi = cur_node->parent->fenzi + cur_node->parent->fenmu;
            cur_node->fenmu = cur_node->parent->fenmu;
        }
        cur_node = cur_node->child;
    }
    if (cur_node->parent->left) {
        cur_node->fenzi = cur_node->parent->fenzi;
        cur_node->fenmu = cur_node->parent->fenzi + cur_node->parent->fenmu;
    } else {
        cur_node->fenzi = cur_node->parent->fenzi + cur_node->parent->fenmu;
        cur_node->fenmu = cur_node->parent->fenmu;
    }

    printf("Case #%d: %lu %lu\n", cur + 1, cur_node->fenzi, cur_node->fenmu);

    while (cur_node != root_node) {
        struct node *child_node = cur_node;
        cur_node = cur_node->parent;
        free(child_node);
    }
    free(cur_node);
    return;
}

void solve2(int cur, unsigned long arg1, unsigned long arg2) {
    struct node *root_node = NULL;
    struct node *leaf_node = NULL;
    struct node *cur_node = (struct node*)malloc(sizeof(struct node));
    leaf_node = cur_node;
    cur_node->child = NULL;
    cur_node->fenzi = arg1;
    cur_node->fenmu = arg2;

    while (cur_node->fenzi != 1 || cur_node->fenmu != 1) {
        struct node *new_node = (struct node*)malloc(sizeof(struct node));
        cur_node->parent = new_node;
        new_node->child = cur_node;
        new_node->parent = NULL;
        if (cur_node->fenzi > cur_node->fenmu) {
            new_node->left = false;
            new_node->fenzi = cur_node->fenzi - cur_node->fenmu;
            new_node->fenmu = cur_node->fenmu;
        } else if (cur_node->fenzi < cur_node->fenmu) {
            new_node->left = true;
            new_node->fenzi = cur_node->fenzi;
            new_node->fenmu = cur_node->fenmu - cur_node->fenzi;
        }
        cur_node = new_node;
    }
    root_node = cur_node;
    root_node->index = 1;

    cur_node = root_node->child;
    while (cur_node != leaf_node) {
        if (cur_node->parent->left) {
            cur_node->index = cur_node->parent->index * 2;
        } else {
            cur_node->index = cur_node->parent->index * 2 + 1;
        }
        cur_node = cur_node->child;
    }
    if (cur_node->parent->left) {
        cur_node->index = cur_node->parent->index * 2;
    } else {
        cur_node->index = cur_node->parent->index * 2 + 1;
    }
    
    printf("Case #%d: %lu\n", cur + 1, cur_node->index);

    while (cur_node != root_node) {
        struct node *child_node = cur_node;
        cur_node = cur_node->parent;
        free(child_node);
    }
    free(cur_node);
    return;
}

int main(int argc, char **argv) {
    char *input_buf = NULL;
    size_t input_size = 0;
    int total_cases = 0;
    int cur_case = 0;

    getline(&input_buf, &input_size, stdin);
    total_cases = atoi(input_buf);
    free(input_buf);
    input_buf = NULL;

    while (cur_case < total_cases) {
        unsigned long arg1 = 0;
        unsigned long arg2 = 0;
        
        getline(&input_buf, &input_size, stdin);
        if (input_buf[0] == '1') {
            sscanf(input_buf, "1 %lu\n", &arg1);
            solve1(cur_case, arg1);
        } else if (input_buf[0] == '2') {
            sscanf(input_buf, "2 %lu %lu\n", &arg1, &arg2);
            solve2(cur_case, arg1, arg2);
        }

        free(input_buf);
        input_buf = NULL;
        cur_case++;
    }
    return 0;
}
