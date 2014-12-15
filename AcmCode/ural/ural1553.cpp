#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int maxn = 100007;

struct Seg {
    int left, right, max_number;
};

struct Seg seg[maxn * 4];
int father[maxn], depth[maxn], vis[maxn], top[maxn], w[maxn], son[maxn], siz[maxn], idx, n;
vector<int> path[maxn];
void build(int order, int left, int right) {
    int mid = (left + right) >> 1;
    seg[order].left = left;
    seg[order].right = right;
    seg[order].max_number = 0;
    if (left >= right) {
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
}

void pushUp(int order) {
    seg[order].max_number = max(seg[order * 2].max_number, seg[order * 2 + 1].max_number);
}

void update(int order, int left, int right, int value) {
    int mid = (seg[order].left + seg[order].right) >> 1;
    if (left == seg[order].left && right == seg[order].right) {
        seg[order].max_number += value;
        return ;
    }
    if (right <= mid) {
        update(order * 2, left, right, value);
    }
    else if (left > mid) {
        update(order * 2 + 1, left, right, value);
    }
    else {
        update(order * 2, left, mid, value);
        update(order * 2 + 1, mid + 1, right, value);
    }
    pushUp(order);
}

int query(int order, int left, int right) {
    int mid = (seg[order].left + seg[order].right) >> 1;
    if (left <= seg[order].left && right >= seg[order].right) {
        return seg[order].max_number;
    }
    if (right <= mid) {
        return query(order * 2, left, right);
    }
    else if (left > mid) {
        return query(order * 2 + 1, left, right);
    }
    else {
        return max(query(order * 2, left, mid), query(order * 2 + 1, mid + 1, right));
    }
}

int findMax(int a, int b) {
    int f1 = top[a];
    int f2 = top[b];
    int ans = query(1, w[a], w[a]);
    while (f1 != f2) {
        if (depth[f1] < depth[f2]) {
            swap(f1, f2);
            swap(a, b);
        }
        ans = max(ans, query(1, w[f1], w[a]));
        a = father[f1];
        f1 = top[a];
    }
    if (a == b) {
        return ans;
    }
    if (depth[a] > depth[b]) {
        swap(a, b);
    }
    return max(ans, query(1, w[a], w[b]));
}

void dfs(int cnt) {
    son[cnt] = 0;
    siz[cnt] = 1;
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i];
        if (!vis[v]) {
            vis[v] = 1;
            depth[v] = depth[cnt] + 1;
            father[v] = cnt;
            dfs(v);
            if (siz[v] > siz[son[cnt]]) {
                son[cnt] = v;
            }
        }
    }
}

void buildTree(int cnt, int anc) {
    top[cnt] = anc;
    w[cnt] = ++idx;
    if (son[cnt]) {
        buildTree(son[cnt], anc);
    }
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i];
        if (v != son[cnt] && v != father[cnt]) {
            buildTree(v, v);
        }
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    memset(siz, 0, sizeof(siz));
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        path[a].push_back(b);
        path[b].push_back(a);
    }
    father[1] = -1;
    vis[1] = 1;
    depth[1] = 0;
    dfs(1);
    buildTree(1, 1);
    build(1, 1, idx);
    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        char temp[10];
        scanf("%s", temp);
        if (temp[0] == 'I') {
            int a, b;
            scanf("%d%d", &a, &b);
            update(1, w[a], w[a], b);
        }
        else {
            int a, b;
            scanf("%d%d", &a, &b);
            printf("%d\n", findMax(a, b));
        }
    }
    return 0;
}
