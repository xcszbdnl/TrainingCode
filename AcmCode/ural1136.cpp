#include <cstdio>
#include <cstring>

const int maxn = 3007;

struct Node {
    int value;
    struct Node *left, *right;
};
int n;
struct Node node[maxn * 100];
int val[maxn], cnt;

struct Node *newNode() {
    node[cnt].left = NULL;
    node[cnt].right = NULL;
    return &node[cnt++];
};

void build(struct Node *cnt_node, int left, int right) {
    cnt_node->value = val[right];
    if (left == right) {
        return ;
    }
    int loc = left - 1;
    int i;
    for (i = left; i <= right - 1; i++) {
        if (val[i] > val[right]) {
            loc = i;
            break;
        }
    }
    if (i == right) {
        loc = right;
    }
    if (loc - left >= 1) {
        cnt_node->left = newNode();
        build(cnt_node->left, left, loc - 1);
    }
    if (right - loc >= 1) {
        cnt_node->right = newNode();
        build(cnt_node->right, loc, right - 1);
    }
}

void printTree(struct Node *cnt_node) {
    if (cnt_node == NULL) {
        return ;
    }
    printTree(cnt_node->right);
    printTree(cnt_node->left);
    printf("%d ", cnt_node->value);
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
    }
    struct Node *root = newNode();
    build(root, 1, n);
    printTree(root);
    printf("\n");
    return 0;
}
