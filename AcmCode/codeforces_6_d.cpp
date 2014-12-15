#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 100007;
struct Seg {
    int left, right, max_num, min_num;
};

struct Seg seg[maxn * 4];
vector<pair<int, int> >ans;
int n, k, val[maxn], loc[maxn];

void pushUp(int order) {
    seg[order].max_num = max(seg[order * 2].max_num, seg[order * 2 + 1].max_num);
    seg[order].min_num = min(seg[order * 2].min_num, seg[order * 2 + 1].min_num);
}
void build(int order, int left, int right) {
    int mid = (left + right) >> 1;
    seg[order].left = left;
    seg[order].right = right;
    if (left == right) {
        seg[order].max_num = seg[order].min_num = val[left];
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
    pushUp(order);
}

int queryMax(int order, int left, int right) {
    int mid = (seg[order].left + seg[order].right) >> 1;
    if (left <= seg[order].left && right >= seg[order].right) {
        return seg[order].max_num;
    }
    if (right <= mid) {
        return queryMax(order * 2, left, right);
    }
    else if (left > mid) {
        return queryMax(order * 2 + 1, left, right);
    }
    else {
        return max(queryMax(order * 2, left, mid), queryMax(order * 2 + 1, mid + 1, right));
    }
}

int queryMin(int order, int left, int right) {
    int mid = (seg[order].left + seg[order].right) >> 1;
    if (left <= seg[order].left && right >= seg[order].right) {
        return seg[order].min_num;
    }
    if (right <= mid) {
        return queryMin(order * 2, left, right);
    }
    else if (left > mid) {
        return queryMin(order * 2 + 1, left, right);
    }
    else {
        return min(queryMin(order * 2, left, mid), queryMin(order * 2 + 1, mid + 1, right));
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
    }
    int max_ans = 0;
    build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        int low = i;
        int high = n;
        while (low <= high) {
            int mid = (low + high) >> 1;
            int max_num = queryMax(1, i, mid);
            int min_num = queryMin(1, i, mid);
            if (max_num - min_num <= k) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        loc[i] = high;
        int len = high - i + 1;
        if (len > max_ans) {
            max_ans = len;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (loc[i] - i + 1 == max_ans) {
            ans.push_back(make_pair(i, loc[i]));
        }
    }
    printf("%d %d\n", max_ans, ans.size());
    for (int i = 0; i < ans.size(); i++) {
        printf("%d %d\n", ans[i].first, ans[i].second);
    }
    return 0;
}
