#include <iostream>
#include <string.h>
#include <cstdio>
#include <vector>

#define MAX_NUMBER 16005
#define INF 1000000
#define max(a,b) ((a) > (b)) ? (a) : (b)

using namespace std;

vector<int> tree[MAX_NUMBER];
int count[MAX_NUMBER];
int dp[MAX_NUMBER];
int ans[MAX_NUMBER], ans_count;
int vis[MAX_NUMBER];
int point_number;

int search(int root) {
    vis[root] = 1;
    int sums = 1;
    for (int i = 0; i < tree[root].size(); i++) {
        int son = tree[root][i];
        if (!vis[son]) {
            sums += search(son);
        }
    }
    count[root] = sums;
    return sums;
}

void getValue(int root) {
    vis[root] = 1;
    int max_count = -1;
    for (int i = 0; i < tree[root].size(); i++) {
        int son = tree[root][i];
        if (!vis[son]) {
            getValue(son);
            max_count = max(max_count, count[son]);
        }
    }
    int left = point_number - count[root];
    max_count = max(max_count, left);
    dp[root] = max_count;
}

int main() {

    scanf("%d", &point_number);
    for (int i = 1; i <= point_number; i++) {
        tree[i].clear();
    }
    for (int i = 1; i < point_number; i++) {
        int point_1, point_2;
        scanf("%d%d", &point_1, &point_2);
        tree[point_1].push_back(point_2);
        tree[point_2].push_back(point_1);
    }
    memset(dp, -1, sizeof(dp));
    memset(count, -1, sizeof(count));
    memset(vis, 0, sizeof(vis));
    search(1);
    memset(vis, 0, sizeof(vis));
    getValue(1);
    int min = INF;
    ans_count = 1;
    for (int i = 1; i <= point_number; i++) {
        if (dp[i] < min) {
            ans_count = 1;
            ans[ans_count] = i;
            min = dp[i];
            ans_count++;
        }
        else if (dp[i] == min) {
            ans[ans_count++] = i;
        }
    }
    ans_count--;
    printf("%d %d\n", min, ans_count);
    for (int i = 1; i <= ans_count; i++) {
        if (i == 1) {
            printf("%d", ans[i]);
        }
        else {
            printf(" %d", ans[i]);
        }
    }
    return 0;
}
