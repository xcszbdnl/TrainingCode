#include <stdio.h>
#include <stdlib.h>

#define MAX_LENTH 11
#define MAX_NUMBER 100005

struct Trei {
    int flag;
    struct Trei *next[MAX_LENTH];
};

char phone_number[MAX_LENTH];
struct Trei node[MAX_NUMBER];
int pointer;

struct Trei *createNewNode() {
    int i;
    struct Trei *new_node = &node[pointer++];
    new_node->flag = 0;
    for (i = 0; i < MAX_LENTH; i++) {
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
        if (cnt_node->flag == 1) {
            return 1;
        }
        i++;
    }
    cnt_node->flag = 1;
    return flag;
}

int main() {

    int i, test_case;
    int word_number, flag;
    struct Trei *root;
    scanf("%d", &test_case);
    pointer = 0;
    while (test_case--) {
        flag = 0;
        scanf("%d", &word_number);
        root = createNewNode();
        for (i = 0; i < word_number; i++) {
            scanf("%s", phone_number);
            if (!flag) {
                flag = insert(root, phone_number);
            }
        }
        if (!flag) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
        pointer = 0;
    }
    return 0;
}
