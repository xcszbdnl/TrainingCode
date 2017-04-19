#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    int check(int health, int **dp, vector<vector<int> >& dungeon) {
        int row = dungeon.size();
        int column = dungeon[0].size();
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                dp[i][j] = -1;
                if (i == 0 && j == 0) {
                    dp[i][j] = health + dungeon[i][j];
                }
                if (i - 1 >= 0) {
                    if (dp[i - 1][j] > 0) {
                        dp[i][j] = dp[i - 1][j] + dungeon[i][j];
                    }
                }
                if (j - 1 >= 0) {
                    if (dp[i][j - 1] > 0) {
                        dp[i][j] = max(dp[i][j], dp[i][j - 1] + dungeon[i][j]);
                    }
                }
            }
        }
        if (dp[row - 1][column - 1] > 0) {
            return true;
        }
        return false;
    }
    int calculateMinimumHP(vector<vector<int> > & dungeon) {
        int row = dungeon.size();
        int column = dungeon[0].size();
        int **dp = (int **)malloc(sizeof(int *) * row);
        for (int i = 0; i < row; i++) {
            dp[i] = (int *)malloc(sizeof(int) * column);
        }
        int high = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                if (dungeon[i][j] < 0) {
                    high -= dungeon[i][j];
                }
            }
        }
        int low = 1;
        while (low <= high) {
            int mid = (low + high) >> 1;
            if (check(mid, dp, dungeon)) {
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        return low;
    }
};
int main() {
    freopen("in.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<int> > maps;
    for (int i = 0; i < n; i++) {
        vector<int> a;
        for (int j = 0; j < m; j++) {
            int c;
            scanf("%d", &c);
            a.push_back(c);
        }
        maps.push_back(a);
    }
    Solution a;
    cout << a.calculateMinimumHP(maps) << endl;
    return 0;
}
