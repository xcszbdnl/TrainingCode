#include <stdio.h>
#include <string.h>

#define MAX_WORDS 1020
#define MAX_TREI 500005
#define MAX_LENTH 25
#define MAX_CHARACTER 30

struct Trei {
    struct Trei *next[MAX_CHARACTER];
    int count;
};

struct Trei node[MAX_TREI];
char word[MAX_WORDS][MAX_LENTH];
char ans[MAX_WORDS][MAX_LENTH];
int pointer, word_number;

struct Trei *createNewNode() {
    int i;
    struct Trei *new_node = &node[pointer++];
    for (i = 0; i < MAX_CHARACTER; i++) {
        new_node->next[i] = NULL;
    }
    new_node->count = 1;
}

void insert(struct Trei *root, char *word) {
    int i, index;
    struct Trei *cnt_node = root;
    i = 0;
    while (word[i]) {
        index = word[i] - 'a';
        if (cnt_node->next[index] == NULL) {
            cnt_node->next[index] = createNewNode();
        }
        else {
            cnt_node->next[index]->count++;
        }
        cnt_node = cnt_node->next[index];
        i++;
    }
}

void solve(struct Trei *root, int order) {
    int i = 0;
    int index;
    struct Trei *cnt_node = root;
    printf("%s ", word[order]);    
    while (word[order][i]) {
        index = word[order][i] - 'a';
        printf("%c", word[order][i]);
        if (cnt_node->next[index]->count == 1) {
            break;
        }
        cnt_node = cnt_node->next[index];
        i++;
    }
    printf("\n");
}

int main() {

    int i;
    struct Trei *root;
    pointer = 0;
    root = createNewNode();
    i = 0;
    while (scanf("%s", word[i]) != EOF) {
        insert(root, word[i]);
        i++;
    }
    word_number = i;
    for (i = 0; i < word_number; i++) {
        solve(root, i);
    }
    return 0;
}
