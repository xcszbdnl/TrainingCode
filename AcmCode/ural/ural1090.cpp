#include <cstdio>
#include <cstring>

const int maxn = 10007;
const int INF = 100000007;
int tree[maxn], n, k;

int lowbit(int x) {
    return x & (-x);
}

int sums(int x) {
    int ret = 0;
    while (x > 0) {
        ret += tree[x];
        x -= lowbit(x);
    }
    return ret;
}

void add(int x, int val) {
    while (x <= n) {
        tree[x] += val;
        x += lowbit(x);
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &k);
    int max_ans = 0;
    int ans = 1;
    for (int i = 1; i <= k; i++) {
        int temp = 0;
        memset(tree, 0, sizeof(tree));
        for (int j = 1; j <= n; j++) {
            int a;
            scanf("%d", &a);
            temp += sums(n) - sums(a);
//            printf("temp:%d\n", temp);
            add(a, 1);
        }
//        printf("%d:%d\n", i, temp);
        if (temp > max_ans) {
            max_ans = temp;
            ans = i;
        }
    }
    printf("%d\n", ans);
}
