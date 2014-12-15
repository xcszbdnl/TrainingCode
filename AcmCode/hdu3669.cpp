#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 500007;

long long dp[107][maxn];
int que[maxn], vis[maxn];
int n, k;

struct People {
    int x, y;
    bool operator < (const struct People &a) const {
        if (x == a.x) {
            return y < a.y;
        }
        return x < a.x;
    }
};


int main() {
    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &k) != EOF) {
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &people[i].x, &people[i].y);
        }
        sort(people + 1, people + 1 + n);
        int pre_y = people[n].y;
        for (int i = n - 1; i >= 1; i--) {
            if (people[i].y > pre_y) {
                pre_y = people[i].y;
            }
            else {
                vis[i] = 1;
            }
        }
        int len = 0;
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                people[++len] = people[i];
            }
        }
        int head, rear;
        dp[0][0] = 0;
        for (int i = 1; i <= k; i++) {
            for (int j = i; j <= len; j++) {
                while (head + 1 < rear && getUp(que[head + 1], que[head]) >= people[j].x * getDown(que[head + 1], que[head])) {
                    head++;
                }
                dp[k][j] =
            }
        }
    }
}
