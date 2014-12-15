#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int maxn = 10007;
const int INF = 100000007;
struct Route {
    int a, b, c;
};
struct Seg {
    int left, right, max_num;
};

struct Route route[maxn];
struct Seg seg[maxn * 4];
vector<pair<int, int> > path[maxn];
int siz[maxn], son[maxn], depth[maxn], father[maxn], w[maxn], vis[maxn], top[maxn];
int idx, max_ans, n;



void build(int order, int left, int right) {
    int mid = (left + right) >> 1;
    seg[order].left = left;
    seg[order].right = right;
    seg[order].max_num = 0;
    if (left == right) {
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
}

void update(int order, int left, int right, int val) {
    int mid = (seg[order].left + seg[order].right) >> 1;
    if (seg[order].left == left && seg[order].right == right) {
        seg[order].max_num = val;
        return ;
    }
    if (right <= mid) {
        update(order * 2, left, right, val);
    }
    else if (left > mid) {
        update(order * 2 + 1, left, right, val);
    }
    else {
        update(order * 2, left, mid, val);
        update(order * 2 + 1, mid + 1, right, val);
    }
    seg[order].max_num = max(seg[order * 2].max_num, seg[order * 2 + 1].max_num);
}

int query(int order, int left, int right) {
    int mid = (seg[order].left + seg[order].right) >> 1;
    if (left <= seg[order].left && right >= seg[order].right) {
        return seg[order].max_num;
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
    int temp = -INF;
    while (f1 != f2) {
        if (depth[f1] < depth[f2]) {
            swap(f1, f2);
            swap(a, b);
        }
        temp = max(temp, query(1, w[f1], w[a]));
        a = father[f1];
        f1 = top[a];
    }
    if (a == b) {
        return temp;
    }
    if (depth[a] > depth[b]) {
        swap(a, b);
    }
    return max(temp, query(1, w[son[a]], w[b]));
}

void dfs(int cnt) {
    siz[cnt] = 1;
    son[cnt] = 0;
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i].first;
        if (!vis[v]) {
            vis[v] = 1;
            father[v] = cnt;
            depth[v] = depth[cnt] + 1;
            dfs(v);
            siz[cnt] += siz[v];
            if (siz[v] > siz[son[cnt]]) {
                son[cnt] = v;
            }
        }
    }
}

void buildTree(int cnt, int anc) {
    w[cnt] = ++idx;
    top[cnt] = anc;
    if (son[cnt]) {
        buildTree(son[cnt], anc);
    }
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i].first;
        if (v != son[cnt] && v != father[cnt]) {
            buildTree(v, v);
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        idx = 0;
        memset(siz, 0, sizeof(siz));
        memset(depth, 0, sizeof(depth));
        memset(w, 0, sizeof(w));
        memset(son, 0, sizeof(son));
        memset(vis, 0, sizeof(vis));
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            path[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            path[a].push_back(make_pair(b, c));
            path[b].push_back(make_pair(a, c));
            route[i].a = a;
            route[i].b = b;
            route[i].c = c;
        }
        vis[1] = 1;
        father[1] = -1;
        dfs(1);
        buildTree(1, 1);
        build(1, 1, idx);
        for (int i = 1; i < n; i++) {
            if (depth[route[i].a] > depth[route[i].b]) {
                swap(route[i].a, route[i].b);
            }
            update(1, w[route[i].b], w[route[i].b], route[i].c);
        }
        char temp[10];
        while (scanf("%s", temp) != EOF) {
            if (temp[0] == 'D') {
                break;
            }
            int a, b;
            scanf("%d%d", &a, &b);
            if (temp[0] == 'Q') {
                int ans = findMax(a, b);
                printf("%d\n", ans);
            }
            else {
                update(1, w[route[a].b], w[route[a].b], b);
            }
        }
    }
}
