#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LENTH 20


struct Trei {
    int flag;
    struct Trei *next[3];
};

char code[MAX_LENTH];

struct Trei *createNewNode() {
    int i;
    struct Trei *new_node = (struct Trei *)malloc(sizeof(struct Trei));
    new_node->flag = 0;
    for (i = 0; i < 3; i++) {
        new_node->next[i] = NULL;
    }
    return new_node;
}

int insert(struct Trei *root, char *word) {
    int i, index, flag;
    struct Trei *cnt_node = root;
    i = 0;
    flag = 1;
    while (word[i]) {
        index = word[i] - '0';
        if (cnt_node->next[index] == NULL) {
            cnt_node->next[index] = createNewNode();
            flag = 0;
        }
        cnt_node = cnt_node->next[index];
        if (cnt_node->flag) {
            return 1;
        }
        i++;
    }
    cnt_node->flag = 1;
    return flag;
}

void delTrei(struct Trei *root) {
    int i;
    for (i = 0; i < 3; i++) {
        if (root->next[i] != NULL) {
            delTrei(root->next[i]);
        }
    }
    free(root);
}


int main() {

    struct Trei *root;
    int flag, set_number = 1;
    flag = 0;
    root = createNewNode();
    while (scanf("%s", code) != EOF) {
        if (strcmp("9", code) == 0) {
            if (!flag) {
                printf("Set %d is immediately decodable\n", set_number);
            }
            else {
                printf("Set %d is not immediately decodable\n", set_number);
            }
            delTrei(root);
            flag = 0;
            root = createNewNode();
            set_number++;
            continue;
        }
        if (!flag) {
            flag = insert(root, code);
        }
    }
    return 0;
}
