#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <queue>
#include <string>
#include <map>
#include <iostream>

using namespace std;
#define MAX_CHARACTER 26
#define MAX_LENTH 1000005
#define MAX_INPUT 60
#define MAX_NUMBER 500000

const int maxn = 100007;
struct Node {
    string cnt_name;
    int num;
    bool operator < (const struct Node &a) const {
        if (num == a.num) {
            return cnt_name > a.cnt_name;
        }
        return num < a.num;
    }
};
struct Trei {
    int flag;
    struct Trei *fail;
    struct Trei *next[MAX_CHARACTER];
};
struct Trei tempNode[maxn];
char key_word[MAX_INPUT];
int cnt_node;
priority_queue<struct Node> que;
map<string, int> maps;
struct Trei *newNode() {
    for (int i = 0; i < 26; i++) {
        tempNode[cnt_node].next[i] = NULL;
    }
    tempNode[cnt_node].fail = NULL;
    tempNode[cnt_node].flag = 0;
    return &tempNode[cnt_node++];
};


void insertWord(struct Trei *root, char *str) {
    int i, index;
    struct Trei *temp;
    temp = root;
    i = 0;
    while (str[i]) {
        index = str[i] - 'a';
        if (temp->next[index] == NULL) {
            temp->next[index] = newNode();
        }
        temp = temp->next[index];
        i++;
    }
    temp->flag++;
}

void query(struct Trei *node, string cnt_name) {
    if (node->flag) {
        struct Node a;
        a.cnt_name = cnt_name;
        a.num = maps[cnt_name];
        que.push(a);
    }
    for (int i = 0; i < 26; i++) {
        if (node->next[i] != NULL) {
            char c = i + 'a';
            query(node->next[i], cnt_name + c);
        }
    }
}
int main() {
    freopen("in.txt", "r", stdin);
    int m;
    scanf("%d", &m);
    struct Trei *root = newNode();
    for (int i = 1; i <= m; i++) {
        char a[20];
        int num;
        scanf("%s%d", a, &num);
        string cnt_name = a;
        maps[cnt_name] = num;
        insertWord(root, a);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        if (i != 1) {
            printf("\n");
        }
        char a[20];
        scanf("%s", a);
        struct  Trei *node = root;
        string cnt_name = "";
        int j;
        for (j = 0; j < strlen(a); j++) {
            int index = a[j] - 'a';
            cnt_name += a[j];
            if (node->next[index] != NULL) {
                node = node->next[index];
            }
            else {
                break;
            }
        }
        if (j == strlen(a)) {
            while (!que.empty()) {
                que.pop();
            }
            query(node, cnt_name);
            int cnt_num = 0;
            while (!que.empty() && cnt_num < 10) {
                struct Node a = que.top();
                que.pop();
                cout << a.cnt_name << endl;
                cnt_num++;
            }
        }
    }
    return 0;
}


