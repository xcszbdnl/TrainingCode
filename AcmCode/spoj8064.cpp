#include <cstdio>
#include <vector>
#include <string>

const int maxn = 107;
int n, k;
vector<int> path[maxn];
int vis[maxn];
int main() {
    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d%d", &n, &k);
        for (int i = 0; i < n; i++) {
            int a;
            scanf("%d", &a);
            path[a].push_back(i);
            path[i].push_back(a);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {

        }
    }
}
