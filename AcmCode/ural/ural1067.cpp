#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 107;

struct Node {
    char name[10];
    int depth;
    vector<struct Node> sons;
    Node() {
        memset(name, 0, sizeof(name));
        depth = 0;
    }
    bool operator < (const struct Node &a) const {
        for (int i = 0; i < strlen(name) && i < strlen(a.name); i++) {
            if (name[i] != a.name[i]) {
                return name[i] < a.name[i];
            }
        }
        return strlen(name) < strlen(a.name);
    }
};
char path[maxn];

void insertPath(struct Node &cnt_node, char *cnt_path) {
    char cnt_name[10];
    if (cnt_path[0] == '\0') {
        return ;
    }
    int loc = strlen(cnt_path);
    int i;
    for (i = 0; i <strlen(cnt_path); i++) {
        if (cnt_path[i] != '\\') {
            cnt_name[i] = cnt_path[i];
        }
        else {
            cnt_name[i] = '\0';
            loc = i + 1;
            break;
        }
    }
    if (i == strlen(cnt_path)) {
        cnt_name[i] = '\0';
    }
    int flag = 0;
    for (int i = 0; i < cnt_node.sons.size(); i++) {
        if (strcmp(cnt_node.sons[i].name, cnt_name) == 0) {
            flag = 1;
            insertPath(cnt_node.sons[i], cnt_path + loc);
            break;
        }
    }
    if (!flag) {
        struct Node cnt_son;
        strcpy(cnt_son.name, cnt_name);
        insertPath(cnt_son, cnt_path + loc);
        cnt_son.depth = cnt_node.depth + 1;
        cnt_node.sons.push_back(cnt_son);
    }
}

void printAns(struct Node cnt_node, int cnt_depth) {
    for (int i = 0; i < cnt_depth; i++) {
        printf(" ");
    }
    sort(cnt_node.sons.begin(), cnt_node.sons.end());
    printf("%s\n", cnt_node.name);
    for (int i = 0; i < cnt_node.sons.size(); i++) {
        printAns(cnt_node.sons[i], cnt_depth + 1);
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    struct Node root;
    root.depth = -1;
    while (n--) {
        scanf("%s", path);
        insertPath(root, path);
    }
    sort(root.sons.begin(), root.sons.end());
//    for (int i = 0; i < root.sons.size(); i++) {
//        printf("%s\n", root.sons[i].name);
//    }
    for (int i = 0; i < root.sons.size(); i++) {
        printAns(root.sons[i], 0);
    }
}
