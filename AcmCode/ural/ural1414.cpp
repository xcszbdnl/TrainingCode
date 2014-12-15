#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1000007;
struct Trei {
    int flag;
    struct Trei *fail;
    struct Trei *next[36];
};

struct Trei tempNode[maxn];
vector<string> ans;
int cnt_node, cnt_num;
char input[50];

struct Trei *newNode() {
    for (int i = 0; i < 36; i++) {
        tempNode[cnt_node].next[i] = NULL;
    }
    tempNode[cnt_node].fail = NULL;
    tempNode[cnt_node].flag = 0;
    return &tempNode[cnt_node++];
};

int getIndex(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    else if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;
    }
}

char getChar(int index) {
    if (index >= 0 && index <= 9) {
        return index + '0';
    }
    else {
        return index - 10 + 'a';
    }
}

void query(struct Trei *cnt, string cnt_name) {
    if (cnt == NULL || cnt_num >= 20) {
        return ;
    }
    if (cnt->flag) {
        cnt_num++;
        ans.push_back(cnt_name);
    }
    for (int i = 0; i < 36; i++) {
        if (cnt->next[i] != NULL) {
            char c = getChar(i);
            query(cnt->next[i], cnt_name + c);
        }
    }
}

void insertWord(struct Trei *root, char *s) {
    struct Trei *temp = root;
    while (*s) {
        int index = getIndex(*s);
        if (temp->next[index] == NULL) {
            temp->next[index] = newNode();
        }
        temp = temp->next[index];
        s++;
    }
    temp->flag++;
}
int main() {
    freopen("in.txt", "r", stdin);
    struct Trei *root = newNode();
    insertWord(root, "sun");
    while (scanf("%s", input) != EOF) {
        if (input[0] == '?') {
            ans.clear();
            cnt_num = 0;
            struct Trei *cnt = root;
            printf("%s\n", input + 1);
            for (int i = 1; i < strlen(input); i++) {
                int index = getIndex(input[i]);
                if (cnt->next[index] != NULL) {
                    cnt = cnt->next[index];
                }
                else {
                    cnt = NULL;
                    break;
                }
            }
            query(cnt, input + 1);
            sort(ans.begin(), ans.end());
            for (int i = 0; i < ans.size(); i++) {
                cout << "  " << ans[i] << endl;
            }
        }
        else {
            insertWord(root, input + 1);
        }
    }
}
