#include <stdio.h>
#include <string.h>


#define MAX_CHARACTER 26
#define MAX_NUMBER 100000
#define MAX_INPUT 1001

struct Trei {
    struct Trei *fail;
    struct Trei *next[MAX_CHARACTER];
    int flag;
};

struct Ans {
    int row;
    int column;
    int direction;
};

struct Trei node[MAX_NUMBER];
struct Trei *queue[MAX_NUMBER];
struct Ans ans[MAX_INPUT];
int direction[][2] = {{-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};
char word_dictionary[MAX_INPUT][MAX_INPUT];
char word_to_find[MAX_INPUT][MAX_INPUT];
int word_lenth[MAX_INPUT];
int pointer, input_row, input_column, word_number;

struct Trei * createNewNode() {
    int i;
    struct Trei *new_node = &node[pointer++];
    new_node->fail = NULL;
    new_node->flag = -1;
    for (i = 0; i < MAX_CHARACTER; i++) {
        new_node->next[i] = NULL;
    }
    return new_node;
}


void insert(struct Trei *root, char *word, int order) {
    int i = 0;
    int index;
    struct Trei *cnt_node = root;
    while (word[i]) {
        index = word[i] - 'A';
        if (cnt_node->next[index] == NULL) {
            cnt_node->next[index] = createNewNode();
        }
        cnt_node = cnt_node->next[index];
        i++;
    }
    cnt_node->flag = order;
}

void buildAc(struct Trei *root) {
    struct Trei *cnt_node, *previous_fail;
    int i, front, rear;
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

int judge(int row, int column) {
    return row >= 0 && row < input_row && column >= 0 && column < input_column;
}

void query(struct Trei *root, int start_row, int start_column, int direction_order) {
    int next_row, next_column;
    int index, i, ans_id;
    struct Trei *cnt_node, *temp;
    next_row = start_row;
    next_column = start_column;
    cnt_node = root;
    while (judge(next_row, next_column)) {
        index = word_dictionary[next_row][next_column] - 'A';
        while (cnt_node->next[index] == NULL && cnt_node != root) {
            cnt_node = cnt_node->fail;
        }
        cnt_node = cnt_node->next[index];
        if (cnt_node == NULL) {
            cnt_node = root;
        }
        temp = cnt_node;
        while (temp != root && temp->flag != -1) {
            ans_id = temp->flag;
            ans[ans_id].row = next_row - (word_lenth[ans_id] - 1) * direction[direction_order][0];
            ans[ans_id].column = next_column - (word_lenth[ans_id] - 1) * direction[direction_order][1];
            ans[ans_id].direction = direction_order;
            temp->flag = -1;
            temp = temp->fail;
        }
        next_row = next_row + direction[direction_order][0];
        next_column = next_column + direction[direction_order][1];
    }
}

void solve(struct Trei *root) {
    int i;
    for (i = 0; i < input_column; i++) {
        query(root, input_row - 1, i, 0); //north direction
        query(root, input_row - 1, i, 1); //north-east direction
        query(root, input_row - 1, i, 7); //north-west direction       
        query(root, 0, i, 3); //south-east direction
        query(root, 0, i, 4); //south direction
        query(root, 0, i, 5); //west-north direction

    }
    for (i = 0; i < input_row; i++) {
        query(root, i, 0, 2); //east direction
        query(root, i, 0, 1); //north-east direction
        query(root, i, 0, 3); //south-east direction
        query(root, i, input_column - 1, 6); //west direction
        query(root, i, input_column - 1, 5); //west-north direction
        query(root, i, input_column - 1, 7); //north-west direction
    }
}

int main() {

    int i;
    struct Trei *root = createNewNode();
    scanf("%d %d %d", &input_row, &input_column, &word_number);
    for (i = 0; i < input_row; i++) {
        scanf("%s", word_dictionary[i]);
    }
    for (i = 0; i < word_number; i++) {
        scanf("%s", word_to_find[i]);
        word_lenth[i] = strlen(word_to_find[i]);
        insert(root, word_to_find[i], i);
    }
    buildAc(root);
    solve(root);
    for (i = 0; i < word_number; i++) {
        printf("%d %d %c\n", ans[i].row, ans[i].column, ans[i].direction + 'A');
    }
}
