#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100007;
struct Seg {
    int left, right;
    int one, twice, more, cover;
};

struct Cube {
    int x1, y1, z1, x2, y2, z2;
};
struct Line {
    int x, y1, y2, flag;
    bool operator < (const struct Line &a) const {
        return x < a.x;
    }
};

struct Cube cube[maxn];
struct Line line[maxn];
struct Seg seg[maxn * 4];
int y[maxn], z[maxn], n, line_num;
long long ans;


void build(int order, int left, int right) {
    int mid = (left + right) >> 1;
    seg[order].left = left;
    seg[order].right = right;
    seg[order].one = seg[order].twice = seg[order].more = seg[order].cover = 0;
    if (left + 1 == right) {
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid, right);
}

void pushUp(int order) {
    if (seg[order].cover > 2) {
        seg[order].more = y[seg[order].right - 1] - y[seg[order].left - 1];
        seg[order].twice = seg[order].one = 0;
    }
    if (seg[order].cover == 2) {
        if (seg[order].left + 1 == seg[order].right) {
            seg[order].twice = y[seg[order].right - 1] - y[seg[order].left - 1];
            seg[order].one = seg[order].more = 0;
        }
        else {
            seg[order].more = seg[order * 2].more + seg[order * 2 + 1].more + seg[order * 2].twice + seg[order * 2 + 1].twice
                              + seg[order * 2].one + seg[order * 2 + 1].one;
            seg[order].twice = y[seg[order].right - 1] - y[seg[order].left - 1] - seg[order].more;
            seg[order].one = 0;
        }
    }
    if (seg[order].cover == 1) {
        if (seg[order].left + 1 == seg[order].right) {
            seg[order].one = y[seg[order].right - 1] - y[seg[order].left - 1];
            seg[order].twice = seg[order].more = 0;
        }
        else {
            seg[order].more = seg[order * 2].more + seg[order * 2 + 1].more + seg[order * 2].twice + seg[order * 2 + 1].twice;
            seg[order].twice = seg[order * 2].one + seg[order * 2 + 1].one;
            seg[order].one = y[seg[order].right - 1] - y[seg[order].left - 1] - seg[order].more - seg[order].twice;
        }
    }
    if (seg[order].cover == 0) {
        if (seg[order].left + 1 == seg[order].right) {
            seg[order].more = seg[order].twice = seg[order].one = 0;
        }
        else {
            seg[order].more = seg[order * 2].more + seg[order * 2 + 1].more;
            seg[order].twice = seg[order * 2].twice + seg[order * 2 + 1].twice;
            seg[order].one = seg[order * 2].one + seg[order * 2 + 1].one;
        }
    }
}

void update(int order, int left, int right, int val) {
    int mid = (seg[order].left +seg[order].right) >> 1;
    if (left <= seg[order].left && right >= seg[order].right) {
        seg[order].cover += val;
        pushUp(order);
        return ;
    }
    if (right <= mid) {
        update(order * 2, left, right, val);
    }
    else if (left >= mid) {
        update(order * 2 + 1, left, right, val);
    }
    else {
        update(order * 2, left, mid, val);
        update(order * 2 + 1, mid, right, val);
    }
    pushUp(order);
}

void addLine(int x, int y1, int y2, int flag) {
    line[line_num].x = x;
    line[line_num].y1 = y1;
    line[line_num].y2 = y2;
    line[line_num].flag = flag;
    line_num++;
}

void solve() {
    sort(y, y + n * 2);
    sort(z, z + n * 2);
    int y_len, z_len;
    y_len = unique(y, y + n * 2) - y;
    z_len = unique(z, z + n * 2) - z;
    build(1, 1, y_len);
    for (int i = 0; i < z_len - 1; i++) {
        line_num = 0;
        for (int j = 0; j < n; j++) {
            if (cube[j].z1 <= z[i] && cube[j].z2 > z[i]) {
                addLine(cube[j].x1, cube[j].y1, cube[j].y2, 1);
                addLine(cube[j].x2, cube[j].y1, cube[j].y2, -1);
            }
        }
        sort(line, line + line_num);
        for (int j = 0; j < line_num; j++) {
            int left = lower_bound(y, y + y_len, line[j].y1) - y + 1;
            int right = lower_bound(y, y + y_len, line[j].y2) - y + 1;
            update(1, left, right, line[j].flag);
            if (j != line_num - 1) {
                ans += (long long)(z[i + 1] - z[i]) * (line[j + 1].x - line[j].x) * seg[1].more;
            }
        }
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    int ncase = 1;
    while (test_case--) {
        printf("Case %d: ", ncase);
        ncase++;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d%d%d%d", &cube[i].x1, &cube[i].y1, &cube[i].z1, &cube[i].x2, &cube[i].y2, &cube[i].z2);
            y[i * 2] = cube[i].y1;
            y[i * 2 + 1] = cube[i].y2;
            z[i * 2] = cube[i].z1;
            z[i * 2 + 1] = cube[i].z2;
        }
        ans = 0;
        solve();
        printf("%I64d\n", ans);
    }
    return 0;

}

