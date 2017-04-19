#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minCut(string s) {
        int len = s.size();
        int **par = (int **)malloc(sizeof(int *) * len);
        int *dp = (int *)malloc(sizeof(int) * (len + 1));
        for (int i = 0; i < len; i++) {
            par[i] = (int *)malloc(sizeof(int) * len);
            dp[i] = len;
        }
        for (int i = 0; i < len; i++) {
            par[i][i] = 1;
            for (int j = i + 1; j < len; j++) {
                par[i][j] = 0;
            }
        }
        dp[len] = -1;
        dp[len - 1] = 0;
        for (int i = len - 2; i >= 0; i--) {
            for (int j = i; j < len; j++) {
                if (s[i] == s[j] && (j - i < 3 || par[i + 1][j - 1])) {
                    par[i][j] = 1;
                    dp[i] = min(dp[i], dp[j + 1] + 1);
                }
            }
        }
        return dp[0];
    }
};


int main() {
    Solution a;
    int r = a.minCut("aaaaaaccc");
    cout << r << endl;
    return 0;
}
