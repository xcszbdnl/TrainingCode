#include <cstdio>
#include <cstring>
#define KEYTREE child[child[root][1]][0]
const int MAX_NUMBER = 300007;
const int INF = 1000000007;

struct Splay {
    inline int min(int a, int b) {
        return a > b ? b : a;
    }
    int child[MAX_NUMBER][2], father[MAX_NUMBER], tree_size[MAX_NUMBER], mem_stack[MAX_NUMBER], mem_queue[MAX_NUMBER];
    int value[MAX_NUMBER], add_lazy[MAX_NUMBER], reverse_lazy[MAX_NUMBER], original_value[MAX_NUMBER], min_number[MAX_NUMBER];
    int root, stack_top, max_top;

    void rotate(int x, int flag) {  //flag == 1, right rotate. flag == 0, left rotate
        int x_father = father[x];
        pushDown(x_father);        
        pushDown(x);
        child[x_father][!flag] = child[x][flag];
        if (child[x][flag]) {
            father[child[x][flag]] = x_father;
        }
        father[x] = father[x_father];
        int grandfather = father[x_father];
        if (grandfather) {
            if (child[grandfather][0] == x_father) {
                child[grandfather][0] = x;
            }
            else {
                child[grandfather][1] = x;
            }
        }
        father[x_father] = x;
        child[x][flag] = x_father;
        pushUp(x_father);
        if (x_father == root) {
            root = x;
        }
    }

    void splay(int x, int goal) {
        pushDown(x);
        for (; father[x] != goal; ) {
            int father_x = father[x];
            int grandfather = father[father_x];
            if (grandfather == goal) { // single rotate
                if (child[father_x][0] == x) {
                    rotate(x, 1);
                }
                else {
                    rotate(x, 0);
                }
            }
            else {
                if (child[grandfather][0] == father_x) {
                    if (child[father_x][0] == x) {
                        rotate(father_x, 1);
                        rotate(x, 1);
                    }
                    else {
                        rotate(x, 0);
                        rotate(x, 1);
                    }
                }
                else {
                    if (child[father_x][1] == x) {
                        rotate(father_x, 0);
                        rotate(x, 0);
                    }
                    else {
                        rotate(x, 1);
                        rotate(x, 0);
                    }
                }
            }
        }
        pushUp(x);
    }
    
    void rotateTo(int order, int goal) {
        int cnt_point = root;
        order++;
        while (cnt_point) {
            int left_size = tree_size[child[cnt_point][0]];
            if (left_size + 1 == order) {
                break;
            }
            else if (order <= left_size) {
                cnt_point = child[cnt_point][0];
            }
            else {
                cnt_point = child[cnt_point][1];
                order = order - (left_size + 1);
            }
        }
        splay(cnt_point, goal);
    }
    void deleteTree(int x) {
        int x_father = father[x];
        int front, rear;
        front = 0;
        rear = 1;
        mem_queue[front] = x;
        while (front < rear) {
            int cnt_point = mem_queue[front];
            mem_stack[stack_top++] = cnt_point;
            int left_child = child[cnt_point][0];
            int right_child = child[cnt_point][1];
            if (left_child) {
                mem_queue[rear++] = left_child;
            }
            if (right_child) {
                mem_queue[rear++] = right_child;
            }
            front++;
        }
        if (child[x_father][0] == x) {
            child[x_father][0] = 0;
        }
        else {
            child[x_father][1] = 0;
        }
        while (x_father != root) {
            pushUp(x_father);
            x_father = father[x_father];
        }
        pushUp(root);
    }

    int pre(int x) {
        pushDown(x);
        int y = child[x][0];
        pushDown(y);
        while (child[y][1]) {
            y = child[y][1];
            pushDown(y);
        }
        return y;
    }
    int succ(int x) {
        pushDown(x);
        int y = child[x][1];
        pushDown(y);
        while (child[y][0]) {
            y = child[y][0];
            pushDown(y);
        }
        return y;
    }
    //the code above do not change often, it is very common in splay tree

    void swap(int &x, int &y) {
        int temp = x;
        x = y;
        y = temp;
    }
    void newNode(int &x, int cnt_value) {
        if (stack_top) {
            x = mem_stack[--stack_top];
        }
        else {
            x = ++max_top;
        }
        child[x][0] = child[x][1] = 0;
        value[x] = cnt_value;
        min_number[x] = cnt_value;
        add_lazy[x] = 0;
        reverse_lazy[x] = 0;
    }
    void init(int n) {
        memset(child, 0, sizeof(child));
        memset(father, 0, sizeof(father));
        memset(tree_size, 0, sizeof(tree_size));
        min_number[0] = value[0] = INF;
        root = stack_top = max_top = 0;
        newNode(root, INF);
        newNode(child[root][1], INF);
        father[child[root][1]] = root;
        buildTree(KEYTREE, 1, n, child[root][1]);
        pushUp(child[root][1]);
        pushUp(root);
    }
    void buildTree(int &cnt_node, int left, int right, int pre_father) {
        if (right < left) {
            return ;
        }
        int mid = (left + right) >> 1;
        newNode(cnt_node, original_value[mid]);
        buildTree(child[cnt_node][0], left, mid - 1, cnt_node);
        buildTree(child[cnt_node][1], mid + 1, right, cnt_node);
        father[cnt_node] = pre_father;
        pushUp(cnt_node);
    }
    
    void pushUp(int x) {
        if (!x) {
            return ;
        }
        int left_child = child[x][0];
        int right_child = child[x][1];
        min_number[x] = min(value[x], min_number[left_child]);
        min_number[x] = min(min_number[x], min_number[right_child]);
        tree_size[x] = 1 + tree_size[left_child] + tree_size[right_child];
    }
    void pushDown(int x) {
        if (!x) {
            return ;
        }
        int left_child = child[x][0];
        int right_child = child[x][1];
        if (add_lazy[x]) {
            value[left_child] += add_lazy[x];
            value[right_child] += add_lazy[x];
            min_number[left_child] += add_lazy[x];
            min_number[right_child] += add_lazy[x];
            add_lazy[left_child] += add_lazy[x];
            add_lazy[right_child] += add_lazy[x];
            add_lazy[x] = 0;
        }
        if (reverse_lazy[x]) {
            reverse_lazy[left_child] ^= 1;
            reverse_lazy[right_child] ^= 1;
            reverse_lazy[x] ^= 1;
            swap(child[left_child][0], child[left_child][1]);
            swap(child[right_child][0],child[right_child][1]);
        }
    }

    void add(int left, int right, int add_value) {
        rotateTo(left - 1, 0);
        rotateTo(right + 1, root);
        value[KEYTREE] += add_value;
        add_lazy[KEYTREE] += add_value;
        min_number[KEYTREE] += add_value;
        pushUp(child[root][1]);
        pushUp(root);
    }

    void reverse(int left, int right) {
        rotateTo(left - 1, 0);
        rotateTo(right + 1, root);
        swap(child[KEYTREE][0], child[KEYTREE][1]);
        reverse_lazy[KEYTREE] ^= 1;
    }

    void revolve(int left, int right, int times) {
        int length = right - left + 1;
        times = (times % length + length) % length;
        if (times == 0) {
            return ;
        }
        reverse(left, right - times);
        reverse(right - times + 1, right);
        reverse(left, right);
    }

    void deleteNode(int loc) {
        rotateTo(loc - 1, 0);
        rotateTo(loc + 1, root);
        deleteTree(KEYTREE);
    }
    void insert(int loc, int cnt_value) {
        rotateTo(loc, 0);
        rotateTo(loc + 1, root);
        newNode(KEYTREE, cnt_value);
        father[KEYTREE] = child[root][1];
        pushUp(child[root][1]);
        pushUp(root);
    }
    
    void query(int left, int right) {
        rotateTo(left - 1, 0);
        rotateTo(right + 1, root);
        printf("%d\n", min_number[KEYTREE]);
    }

    void printTree(int cnt_point) {
        if (child[cnt_point][0]) {
            printTree(child[cnt_point][0]);
        }
        printf("%d:%d\n", cnt_point, value[cnt_point]);
        if (child[cnt_point][1]) {
            printTree(child[cnt_point][1]);
        }
    }
};

struct Splay splay_tree;
int main() {
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &splay_tree.original_value[i]);
    }
    splay_tree.init(n);
    //splay_tree.printTree(splay_tree.root);
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
            //splay_tree.printTree(splay_tree.root);
        }
        else if (op[0] == 'R' && op[3] == 'E') {
            scanf("%d%d", &left, &right);
            splay_tree.reverse(left, right);
        }
        else if (op[0] == 'R' && op[3] == 'O') {
            int times;
            scanf("%d%d%d", &left, &right, &times);
            //splay_tree.printTree(splay_tree.root);
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
            splay_tree.query(left, right);
        }
        //splay_tree.printTree(splay_tree.root);
    }
    return 0;
}
