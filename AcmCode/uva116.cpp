#include <string.h>
#include <cstdio>
#include <iostream>


#define MAX_NUMBER 200
#define INF 20000000
#define min(a,b) ((a) > (b)) ? (a) : (b)

using namespace std;

long long maps[MAX_NUMBER][MAX_NUMBER];
long long dp[MAX_NUMBER][MAX_NUMBER];
int next_row[MAX_NUMBER][MAX_NUMBER];
int vis[MAX_NUMBER][MAX_NUMBER];
int row, column;


void search(int cnt_row, int cnt_column) {
    if (vis[cnt_row][cnt_column]) {
        return ;
    }
    if (cnt_row == 1) {
        long long min_ans = INF;
        search(cnt_row, cnt_column + 1);
        if (dp[cnt_row][cnt_column + 1] < min_ans) {
            min_ans = dp[cnt_row][cnt_column + 1];
            next_row[cnt_row][cnt_column] = cnt_row;
            
        }
        search(cnt_row + 1, cnt_column + 1);
        if (dp[cnt_row + 1][cnt_column + 1] < min_ans) {
            min_ans = dp[cnt_row + 1][cnt_column + 1];
            next_row[cnt_row][cnt_column] = cnt_row + 1;
        }
        search(row, cnt_column + 1);
        if (dp[row][cnt_column + 1] < min_ans) {
            min_ans = dp[row][cnt_column + 1];
            next_row[cnt_row][cnt_column] = row;
        }
        dp[cnt_row][cnt_column] = min_ans + maps[cnt_row][cnt_column];
    }
    else if (cnt_row == row) {
        long long min_ans = INF;
        search(1, cnt_column + 1);
        if (dp[1][cnt_column + 1] < min_ans) {
            min_ans = dp[1][cnt_column + 1];
            next_row[cnt_row][cnt_column] = 1;
        }
        search(cnt_row - 1, cnt_column + 1);
        if (dp[cnt_row - 1][cnt_column + 1] < min_ans) {
            min_ans = dp[cnt_row - 1][cnt_column + 1];
            next_row[cnt_row][cnt_column] = cnt_row - 1;
        }
        search(cnt_row, cnt_column + 1);
        if (dp[cnt_row][cnt_column + 1] < min_ans) {
            min_ans = dp[cnt_row][cnt_column + 1];
            next_row[cnt_row][cnt_column] = cnt_row;
        }
        dp[cnt_row][cnt_column] = min_ans + maps[cnt_row][cnt_column];
    }
    else {
        long long min_ans = INF;
        search(cnt_row - 1, cnt_column + 1);
        if (dp[cnt_row - 1][cnt_column + 1] < min_ans) {
            min_ans = dp[cnt_row - 1][cnt_column + 1];
            next_row[cnt_row][cnt_column] = cnt_row - 1;
        }
        search(cnt_row, cnt_column + 1);
        if (dp[cnt_row][cnt_column + 1] < min_ans) {
            min_ans = dp[cnt_row][cnt_column + 1];
            next_row[cnt_row][cnt_column] = cnt_row;
        }
        search(cnt_row + 1, cnt_column + 1);
        if (dp[cnt_row + 1][cnt_column + 1] < min_ans) {
            min_ans = dp[cnt_row + 1][cnt_column + 1];
            next_row[cnt_row][cnt_column] = cnt_row + 1;
        }
        dp[cnt_row][cnt_column] = min_ans + maps[cnt_row][cnt_column];        
    }
    vis[cnt_row][cnt_column] = 1;
}

int main() {

    while (scanf("%d%d", &row, &column) != EOF) {
        memset(dp, -1, sizeof(dp));
        memset(next_row, -1, sizeof(next_row));
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= column; j++) {
                cin >> maps[i][j];
            }
        }
        for (int i = 1; i <= row ;i++) {
            dp[i][column] = maps[i][column];
            vis[i][column] = 1;
        }
        for (int i = 1; i <= row; i++) {
            search(i, 1);
        }
        long long ans = INF;
        int ans_row;
        for (int i = 1; i <= row; i++) {
            if (dp[i][1] < ans) {
                ans = dp[i][1];
                ans_row = i;
            }
        }
        int cnt_row = ans_row;
        for (int i = 1; i <= column ; i++) {
            if (i == 1) {
                printf("%d", cnt_row);
            }
            else {
                printf(" %d", cnt_row);                
            }
            cnt_row = next_row[cnt_row][i];
        }
        printf("\n");
        cout << ans << endl;
    }
    
}

