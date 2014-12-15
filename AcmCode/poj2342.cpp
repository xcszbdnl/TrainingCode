#include <iostream>
#include <cstdio>
#include <vector>
#include <string.h>

using namespace std;

#define MAX_NUMBER 6004
#define max(a,b) ((a) > (b)) ? (a) : (b)

vector<int> tree[MAX_NUMBER];
int rating[MAX_NUMBER], vis[MAX_NUMBER];
int point_number;
int dp[MAX_NUMBER][2];

int search(int root, int invited) {
    if (dp[root][invited] != -1) {
        return dp[root][invited];
    }
    if (invited) {
        int sums = rating[root];
        for (int i = 0; i < tree[root].size(); i++) {
            int son = tree[root][i];
            sums += search(son, 0);
        }
        dp[root][invited] = sums;
        return sums;
    }
    else {
        int sums = 0;
        for (int i = 0; i < tree[root].size(); i++) {
            int son = tree[root][i];
            sums += max(search(son, 0), search(son, 1));
        }
        dp[root][invited] = sums;
        return sums;
    }
}


int main() {

    while (scanf("%d", &point_number) != EOF) {
        memset(vis, 0, sizeof(vis));
        memset(dp, -1, sizeof(dp));
        for (int i = 1; i <= point_number; i++) {
            scanf("%d", &rating[i]);
            tree[i].clear();
        }

        for (int i = 1; i < point_number; i++) {
            int employee, boss;
            scanf("%d%d", &employee, &boss);
            vis[employee] = 1;
            tree[boss].push_back(employee);
        }
        int temp_1, temp_2;
        scanf("%d%d", &temp_1, &temp_2);
        for (int i = 1; i <= point_number; i++) {
            if (tree[i].size() == 0) {
                dp[i][0] = 0;
                dp[i][1] = rating[i];
            }
        }
        int ans;
        for (int i = 1; i <= point_number; i++) {
            if (!vis[i]) {
                search(i, 0);
                search(i, 1);
                ans = max(dp[i][0], dp[i][1]);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
