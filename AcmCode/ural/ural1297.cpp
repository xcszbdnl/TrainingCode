#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 10007;

char str[maxn * 4];
int wa[maxn], wb[maxn], ws[maxn], wv[maxn], sa[maxn], str_rank[maxn], height[maxn];
int m, n, dp[maxn][32];
int cmp(int *r, int a, int b, int l) {
    return r[a] == r[b] && r[a + l] == r[b + l];
}

void da() {
    int i, j, p, *x = wa, *y = wb, *t;
    for (i = 0; i < m; i++) {
        ws[i] = 0;
    }
    for (i = 0; i < n; i++) {
        ws[x[i] = str[i]]++;
    }
    for (i = 1; i < m; i++) {
        ws[i] += ws[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        sa[--ws[x[i]]] = i;
    }
    for (j = 1, p = 1; p < n; j *= 2, m = p) {
        for (p = 0, i = n - j; i < n; i++) {
            y[p++] = i;
        }
        for (i = 0; i < n; i++) {
            if (sa[i] >= j) {
                y[p++] = sa[i] - j;
            }
        }
        for (i = 0; i < n; i++) {
            wv[i] = x[y[i]];
        }
        for (i = 0; i < m; i++) {
            ws[i] = 0;
        }
        for (i = 0; i < n; i++) {
            ws[wv[i]]++;
        }
        for (i = 1; i < m; i++) {
            ws[i] += ws[i - 1];
        }
        for (i = n - 1; i >= 0; i--) {
            sa[--ws[wv[i]]] = y[i];
        }
        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++) {
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1: p++;
        }
    }
    return ;
}

void calHeight() {
    int j, k = 0;
    for (int i = 1; i < n; i++) {
        str_rank[sa[i]] = i;
    }
    for (int i = 0; i < n; height[str_rank[i++]] = k) {
        for (k?k--:0, j = sa[str_rank[i] - 1]; str[i + k] == str[j + k]; k++);
    }
}

void init() {
    for (int i = 0; i < n; i++) {
        dp[i][0] = height[i];
    }
    for (int j = 1; (1 << j) < n; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int rmp(int l,int r) {
    int k = 0;
    while (1 << (k + 1) <= r - l + 1) k++;
    return min(dp[l][k], dp[r - (1 << k) + 1][k]);
}

int lcp(int s1, int s2) {
    int a = str_rank[s1], b = str_rank[s2];
    if (a > b) {
        swap(a, b);
    }
    return rmp(a + 1, b);
}


int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%s", str) != EOF) {
        m = 127;
        int k;
        k = n = strlen(str);
        str[n] = '$';
        for (int i = 0; i < n; i++) {
            str[n + 1 + i] = str[n - i - 1];
        }
        n = 2 * n + 1;
        str[n++] = 0;
        da();
        calHeight();
        init();
        int ans = 0;
        int idx = 0;
        for (int i = 0; i < k; i++) {
            int tmp = lcp(i, n - 2 - i);
            if (tmp * 2 - 1 > ans) {
                ans = tmp * 2 - 1;
                idx = i - tmp + 1;
            }
            if (str[i] == str[i + 1]) {
                tmp = lcp(i, n - 3 - i);
                if (tmp * 2 - 2 > ans) {
                    ans = tmp * 2 - 2;
                    idx = i - tmp + 2;
                }
            }
        }
        for (int i = 0; i < ans; i++) {
            printf("%c", str[idx + i]);
        }
        printf("\n");
    }
    return 0;
}
