#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;
const int maxn = 100007;

struct Seg {
    int left, right;
    long long sum, lazy;
};

struct Seg seg[maxn * 4];
int dfs_block;
long long salary[maxn], val[maxn];
int low[maxn], high[maxn], vis[maxn], n, m;
vector<int> path[maxn];
void pushUp(int order) {
    seg[order].sum = seg[order * 2].sum + seg[order * 2 + 1].sum;
    return ;
}

void pushDown(int order) {
    if (seg[order].lazy) {
        seg[order * 2].sum += (seg[order * 2].right - seg[order * 2].left + 1) * seg[order].lazy;
        seg[order * 2 + 1].sum += (seg[order * 2 + 1].right - seg[order * 2 + 1].left + 1) * seg[order].lazy;
        seg[order * 2].lazy +=  seg[order].lazy;
        seg[order * 2 + 1].lazy += seg[order].lazy;
        seg[order].lazy = 0;
    }
}

void build(int order, int left, int right) {
    int mid = (left + right) >> 1;
    seg[order].left = left;
    seg[order].right = right;
    seg[order].lazy = 0;
    if (left == right) {
        seg[order].sum = val[left];
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
    pushUp(order);
}

long long query(int order, int left, int right) {
    int mid = (seg[order].left + seg[order].right) >> 1;
    if (left <= seg[order].left && right >= seg[order].right) {
        return seg[order].sum;
    }
    pushDown(order);
    if (right <= mid) {
        return query(order * 2, left, right);
    }
    else if (left > mid) {
        return query(order * 2 + 1, left, right);
    }
    else {
        return query(order * 2, left, mid) + query(order * 2 + 1, mid + 1, right);
    }
}

void update(int order, int left, int right, long long cnt_val) {
    int mid = (seg[order].left + seg[order].right) >> 1;
    if (left <= seg[order].left && right >= seg[order].right) {
        seg[order].lazy += cnt_val;
        seg[order].sum += (seg[order].right - seg[order].left + 1) * cnt_val;
        return ;
    }
    pushDown(order);
    if (right <= mid) {
        update(order * 2, left, right, cnt_val);
    }
    else if (left > mid) {
        update(order * 2 + 1, left, right, cnt_val);
    }
    else {
        update(order * 2, left, mid, cnt_val);
        update(order * 2 + 1, mid + 1, right, cnt_val);
    }
    pushUp(order);
}

void dfs(int cnt) {
    low[cnt] = ++dfs_block;
    for (int i = 0; i < path[cnt].size(); i++) {
        int v = path[cnt][i];
        if (!vis[v]) {
            vis[v] = 1;
            dfs(v);
        }
    }
    high[cnt] = dfs_block;
}
int main() {
//    freopen("in.txt", "r", stdin);
    dfs_block = 0;
    int cnt_s;
    scanf("%d%d%d", &n, &m, &cnt_s);
    salary[0] = cnt_s;
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        path[a].push_back(i);
        path[i].push_back(a);
        salary[i] = b;
    }
    vis[0] = 1;
    dfs(0);
    for (int i = 0; i < n; i++) {
        val[low[i]] = salary[i];
    }
//    for (int i = 0; i < n; i++) {
//        printf("%d ", low[i]);
//    }
//    printf("\n");
    build(1, 1, dfs_block);
    for (int i = 1; i <= m; i++) {
        char temp[20];
        long long a, b, c;
        cin >> temp >> a >> b >> c;
        if (temp[0] == 'e') {
            long long cnt_s = query(1, low[a], low[a]);
            if (cnt_s < b) {
                update(1, low[a], low[a], c);
            }
        }
        else {
            long long cnt_s = query(1, low[a], high[a]);
            double ave = cnt_s * 1.0 / (high[a] - low[a] + 1);
            if (ave < b) {
                update(1, low[a], high[a], c);
            }
        }
    }
    for (int i = 1; i <= dfs_block; i++) {
        val[i] = query(1, i, i);
    }
    for (int i = 0; i < n; i++) {
        cout << val[low[i]] << endl;
    }
    return 0;
}


