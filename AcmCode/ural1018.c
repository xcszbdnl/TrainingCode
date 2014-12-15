#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 200

struct Point {
    int left;
    int right;
    int value;
};

struct Point point[MAX_NUMBER];
int point_number, edge_number;
int dp[MAX_NUMBER][MAX_NUMBER], vis[MAX_NUMBER];

int search(int root, int number) {
    int i, max, l_ans, r_ans;
    if (number == 0 || root == -1) {
        return 0;
    }
    
    if (dp[root][number] != -1) {
        return dp[root][number];
    }
    max = 0;
    for (i = 0; i < number; i++) {
        l_ans = search(point[root].left, i);
        r_ans = search(point[root].right, number - i - 1);
        if (l_ans + r_ans > max) {
            max = l_ans + r_ans;
        }
    }
    max += point[root].value;
    dp[root][number] = max;
    return dp[root][number];
}

int main() {

    int i, j, value, ans, point_1, point_2;
    scanf("%d%d", &point_number, &edge_number);
    memset(point, -1, sizeof(point));
    memset(dp, -1, sizeof(dp));
    memset(vis, 0, sizeof(vis));
    vis[1] = 1;
    for (i = 1; i < point_number; i++) {
        scanf("%d%d%d", &point_1, &point_2, &value);
        if (vis[point_1]) {
            if (point[point_1].left == -1) {
                point[point_1].left = point_2;
            }
            else {
                point[point_1].right = point_2;
            }
            point[point_2].value = value;
            vis[point_2] = 1;
        }
        else {
            if (point[point_2].left == -1) {
                point[point_2].left = point_1;
            }
            else {
                point[point_2].right = point_1;
            }
            point[point_1].value = value;
            vis[point_1] = 1;
        }
    }
    point[1].value = 0;
    ans = search(1, edge_number + 1);
    printf("%d\n", ans);
}
