#include <string.h>
#include <stdio.h>


#define MAX_NUMBER 200
#define INF 1000000


int map[MAX_NUMBER][MAX_NUMBER];
int vis[MAX_NUMBER], son_number[MAX_NUMBER];
int dp[MAX_NUMBER][MAX_NUMBER];
int point_number, preserve_number;

void search(int root) {
    int i, son;
    for (i = 0; i <= preserve_number; i++) {
        dp[root][i] = INF;
    }
    dp[root][1] = 0;
    for (i = 0; i < son_number[root]; i++) {
        sons = map[root][i];
        search(root);
        for (k = 0; k <= number; k++) {
            
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int i, parent, son, ans;
    scanf("%d%d", &point_number, &preserve_number);
    memset(vis, 0, sizeof(vis));
    memset(son_number, 0, sizeof(son_number));
    for (i = 1; i < point_number; i++) {
        scanf("%d%d", &parent, &son);
        map[parent][son_number[parent]] = son;
        son_number[parent]++;
        vis[son] = 1;
    }
    for (i = 1; i <= point_number; i++) {
        if (!vis[i]) {
            search(i);
        }
    }
    ans = dp[root][preserve_number];
    for (i = 1; i <= point_number; i++) {
        if (dp[i][preserve_number] + 1 < ans) {
            ans = dp[i][preserve_number] + 1;
        }
    }
    printf("%d\n", preserve_number);
}
