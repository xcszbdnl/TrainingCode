#include <cstdio>
#include <cstring>

const int maxn = 100007;
const long long INF = 2000000000ll;
int n, m, w;
long long temp[maxn], val[maxn];
long long tree[maxn];
int lowbit(int x) {
    return x & (-x);
}

void add(int x, int cnt_val) {
    while (x <= n) {
        tree[x] += cnt_val;
        x += lowbit(x);
    }
}

long long sum(int x) {
    long long ret = 0;
    while (x > 0) {
        ret += tree[x];
        x -= lowbit(x);
    }
    return ret;
}

bool check(long long cnt) {
    long long cnt_time = 0;
    for (int i = 1; i <= n; i++) {
        long long cnt_num = sum(i) + val[i];
        if (cnt_num < cnt) {
            cnt_time += cnt - cnt_num;
            add(i, cnt - cnt_num);
            add(i + w, cnt_num - cnt);
        }
        if (cnt_time > m) {
            return false;
        }
    }
    return true;
}

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d%d", &n, &m, &w);
    memset(tree, 0, sizeof(tree));
    for (int i = 1; i <= n; i++) {
        scanf("%I64d", &val[i]);
    }
    long long low = 1;
    long long high = INF;
    while (low <= high) {
        long long mid = (low + high) / 2;
        for (int i = 0; i <= n; i++) {
            tree[i] = 0;
        }
        if (check(mid)) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    printf("%I64d\n", high);
    return 0;
}
