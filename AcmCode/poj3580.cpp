#include <cstdio>
#include <cstring>
const int INF = 10000007;
const int MAX_POINT = 100007;


struct SplayTree {
    #define dealTree child[child[root][1]][0]
    int child[MAX_POINT][2];
    int fa[MAX_POINT];
    int value[MAX_POINT];
    int input[MAX_POINT];
    int add_lazy[MAX_POINT];
    int reverse_lazy[MAX_POINT];
    int min_number[MAX_POINT];
    int sums[MAX_POINT];
    int tree_size[MAX_POINT];
    int que[MAX_POINT];
    int mem_sta[MAX_POINT];
    int top_1, top_2, root;
    inline void swap(int &x, int &y) {
        int temp = x;
        x = y;
        y = temp;
    }

    inline void rotate(int x, int c) {
        int y = fa[x];
        pushDown(y);
        pushDown(x);
        child[y][!c] = child[x][c];
        fa[child[x][c]] = y;
        fa[x] = fa[y];
        if (fa[x]) {
            child[fa[x]][child[fa[y]][1] == y] = x;
        }
        child[x][c] = y;
        fa[y] = x;
        pushUp(y);
    }

    inline void splay(int x, int goal) {
        pushDown(x);
        while (fa[x] != goal) {
            if (fa[fa[x]] == goal) {
                rotate(x, x == child[fa[x]][0]);
            }
            else {
                int y = fa[x];
                int z = fa[y];
                int f = child[z][0] == y;
                if (child[y][f] == x) {
                    rotate(x, !f);
                    rotate(x, f);
                }
                else {
                    rotate(y, f);
                    rotate(x, f);
                }
            }
        }
        pushUp(x);
        if (goal == 0) {
            root = x;
        }
    }
    inline void rotateTo(int k, int goal) {
        int x = root;
        pushDown(x);
        k++;
        while (tree_size[child[x][0]] != k - 1) {
            if (k - 1 < tree_size[child[x][0]]) {
                x = child[x][0];
            }
            else {
                k = k - tree_size[child[x][0]] - 1;
                x = child[x][1];
            }
            pushDown(x);
        }
        splay(x, goal);
    }
    inline void deleteTree(int x) {
        int cnt_father = fa[x];
        int front = 0;
        int rear = 1;
        que[front] = x;
        while (front < rear) {
            mem_sta[top_2++] = que[front];
            if (child[que[front]][0]) {
                que[rear++] = child[que[front]][0];
            }
            if (child[que[front]][1]) {
                que[rear++] = child[que[front]][1];
            }
            front++;            
        }
        child[cnt_father][x == child[cnt_father][0]] = 0;
        while (cnt_father != root) {
            pushUp(cnt_father);
            cnt_father = fa[cnt_father];
        }
        pushUp(root);
    }
    inline int pre(int x) {
        pushDown(x);
        int y = child[x][0];
        pushDown(y);
        while (child[y][1]) {
            y = child[y][1];
            pushDown(y);
        }
        return y;
    }
    inline int suc(int x) {
        pushDown(x);
        int y = child[x][1];
        pushDown(y);
        while (child[y][0]) {
            y = child[y][0];
            pushDown(y);
        }
        return y;
    }
    //the code above will not change often, because it is almost always useful for all splay trees
    inline void newNode(int &x, int cnt_value) {
        if (top_2) {
            x = mem_sta[--top_2];
        }
        else {
            x = ++top_1;
        }
        child[x][0] = child[x][1] = 0;
        tree_size[x] = 1;
        value[x] = cnt_value;
        min_number[x] = cnt_value;
        add_lazy[x] = 0;
        reverse_lazy[x] = 0;
    }
    inline void makeTree(int &x, int left, int right, int *arr, int father) {
        if (left > right) {
            return ;
        }
        int mid = (left + right) >> 1;
        newNode(x, arr[mid]);
        makeTree(child[x][0], left, mid - 1, arr, x);
        makeTree(child[x][1], mid + 1, right, arr, x);
        fa[x] = father;
        pushUp(x);
    }

    inline void init(int n) {
        fa[0] = tree_size[0] = child[0][0] = child[0][1] = 0;
        root = 0;
        add_lazy[0] = reverse_lazy[0] = 0;
        value[0] = min_number[0] = INF;
        top_1 = 0;
        top_2 = 0;
        newNode(root, INF);
        newNode(child[root][1], INF);
        fa[child[root][1]] = root;
        makeTree(dealTree, 1, n, input, child[root][1]);
        pushUp(child[root][1]);
        pushUp(root);
    }

    inline void add(int left, int right, int cnt_value) {
        rotateTo(left - 1, 0);
        rotateTo(right + 1, root);
        value[dealTree] += cnt_value; 
        add_lazy[dealTree] += cnt_value;
        min_number[dealTree] += cnt_value;
        pushUp(child[root][1]);
        pushUp(root);
    }

    inline void reverse(int left, int right) {
        rotateTo(left - 1, 0);
        rotateTo(right + 1, root);
        swap(child[dealTree][0], child[dealTree][1]);
        reverse_lazy[dealTree] ^= 1;
    }

    inline void revolve(int left, int right, int times) {
        int length = right - left + 1;
        times = (times % length + length) % length;
        reverse(left, right - times);
        reverse(right - times + 1, right);
        reverse(left, right);
    }
    inline void deleteNode(int loc) {
        rotateTo(loc - 1, 0);
        rotateTo(loc + 1, root);
        deleteTree(dealTree);
    }
    inline void insert(int loc, int value) {
        rotateTo(loc, 0);
        rotateTo(loc + 1, root);
        newNode(dealTree, value);
        fa[dealTree] = child[root][1];
        pushUp(child[root][1]);
        pushUp(root);
    }

    inline int query(int left, int right) {
        rotateTo(left - 1, 0);
        rotateTo(right + 1, root);
        return min_number[dealTree];
    }

    inline void printTree() {
        printNode(root);
        printf("\n");
    }
    inline void printNode(int x) {
        pushDown(x);
        if (child[x][0]) {
            printNode(child[x][0]);
        }
        printf("%d ", value[x]);
        if (child[x][1]) {
            printNode(child[x][1]);
        }
    }
    inline void pushDown(int x) {
        if (x == 0) {
            return ;
        }
        int left_child = child[x][0];
        int right_child = child[x][1];
        if (add_lazy[x]) {
            value[left_child] += add_lazy[x];
            add_lazy[left_child] += add_lazy[x];
            min_number[left_child] += add_lazy[x];
            sums[left_child] += add_lazy[x] * tree_size[left_child];
            value[right_child] += add_lazy[x];
            add_lazy[right_child] += add_lazy[x];
            min_number[right_child] += add_lazy[x];
            sums[right_child] += add_lazy[x] * tree_size[right_child];
            add_lazy[x] = 0;
        }
        if (reverse_lazy[x]) {
            reverse_lazy[left_child] ^= 1;
            reverse_lazy[right_child] ^= 1;
            reverse_lazy[x] ^= 1;
            swap(child[left_child][0], child[left_child][1]);
            swap(child[right_child][0], child[right_child][1]);
        }
    }
    
    inline void pushUp(int x) {
        int left_child = child[x][0];
        int right_child = child[x][1];
        tree_size[x] = tree_size[left_child] + tree_size[right_child] + 1;
        sums[x] = sums[left_child] + sums[right_child];
        min_number[x] = min(min_number[left_child], min_number[right_child]);
        min_number[x] = min(min_number[x], value[x]);
    }
    inline int min(int a, int b) {
        return a > b ? b : a;
    }
};

struct SplayTree splay_tree;


int main() {

    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &splay_tree.input[i]);
    }
    splay_tree.init(n);
    int operation_number;
    scanf("%d", &operation_number);
    for (int i = 1; i <= operation_number; i++) {
        int left, right;
        char op[10];
        scanf("%s", &op);
        if (op[0] == 'A') {
            int value;
            scanf("%d%d%d", &left, &right, &value);
            splay_tree.add(left, right, value);
        }
        else if (op[0] == 'R' && op[3] == 'E') {
            scanf("%d%d", &left, &right);
            splay_tree.reverse(left, right);
        }
        else if (op[0] == 'R' && op[3] == 'O') {
            int times;
            scanf("%d%d%d", &left, &right, &times);
            splay_tree.revolve(left, right, times);
        }
        else if (op[0] == 'I') {
            int value;
            scanf("%d%d", &left, &value);
            splay_tree.insert(left, value);
        }
        else if (op[0] == 'D') {
            scanf("%d", &left);
            splay_tree.deleteNode(left);
        }
        else if (op[0] == 'M') {
            scanf("%d%d", &left, &right);
            int ans = splay_tree.query(left, right);
            printf("%d\n", ans);
        }
    }
    return 0;
}

