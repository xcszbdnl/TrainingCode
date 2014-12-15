#include <stdio.h>
#include <stdlib.h>

#define MAX_CHARACTER 26
#define MAX_LENTH 1000005
#define MAX_INPUT 60
#define MAX_NUMBER 500000

struct Trei {
    int flag;
    struct Trei *fail;
    struct Trei *next[MAX_CHARACTER];
};
struct Trei *queue[MAX_NUMBER];
char description[MAX_LENTH];
char key_word[MAX_INPUT];

struct Trei *createNewNode() {
    int i;
    struct Trei *new_node = (struct Trei *)malloc(sizeof(struct Trei));
    new_node->flag = 0;
    new_node->fail = NULL;
    for (i = 0; i < MAX_CHARACTER; i++) {
        new_node->next[i] = NULL;
    }
    return new_node;
}


void insert(struct Trei *root, char *str) {
    int i, index;
    struct Trei *temp;
    temp = root;
    i = 0;
    while (str[i]) {
        index = str[i] - 'a';
        if (temp->next[index] == NULL) {
            temp->next[index] = createNewNode();
        }
        temp = temp->next[index];
        i++;
    }
    temp->flag++;
}

void buildAc(struct Trei *root) {
    struct Trei *cnt_node, *previous_fail;
    int i;
    int front, rear;
    root->fail = NULL;
    front = 0, rear = 1;
    queue[front] = root;
    while (front < rear) {
        cnt_node = queue[front++];
        for (i = 0; i < MAX_CHARACTER; i++) {
            if (cnt_node->next[i] != NULL) {
                if (cnt_node == root) {
                    cnt_node->next[i]->fail = root;
                }
                else {
                    previous_fail = cnt_node->fail;
                    while (previous_fail != NULL) {
                        if (previous_fail->next[i] != NULL) {
                            cnt_node->next[i]->fail = previous_fail->next[i];
                            break;
                        }
                        previous_fail = previous_fail->fail;
                    }
                    if (previous_fail == NULL) {
                        cnt_node->next[i]->fail = root;
                    }
                }
                queue[rear++] = cnt_node->next[i];
            }
        }
    }
}

int query(struct Trei *root, char *str) {
    int index, i, ans;
    struct Trei *node, *temp;
    ans = 0;
    node = root;
    i = 0;
    while (str[i]) {
        index = str[i] - 'a';
        while (node->next[index] == NULL && node != root) {
            node = node->fail;
        }
        node = node->next[index];
        if (node == NULL) {
            node = root;
        }
        temp = node;
        while (temp != root && temp->flag != -1) {
            ans += temp->flag;
            temp->flag = -1;
            temp = temp->fail;
        }
        i++;
    }
    return ans;
}

void delTrei(struct Trei *root) {
    int i;
    for (i = 0; i < MAX_CHARACTER; i++) {
        if (root->next[i] != NULL) {
            delTrei(root->next[i]);
        }
    }
    free(root);
}

int main() {

    int test_case, key_word_number;
    int i, number;
    struct Trei *root;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d", &key_word_number);
        root = createNewNode();
        for (i = 0; i < key_word_number; i++) {
            scanf("%s", key_word);
            insert(root, key_word);
        }
        buildAc(root);
        scanf("%s", description);
        number = query(root, description);
        printf("%d\n", number);
        delTrei(root);
    }
    return 0;
}

