#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        vector<map<long long, long long> > dp(A.size());
        int ret = 0;
//        sort(A.begin(), A.end());
//        long long max_diff = A[A.size() - 1] - A[0];
        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < i; j++) {
                long long diff = (long long)A[i] - A[j];
                if (dp[i].count(diff)) {
                    dp[i][diff] += 1;
                }
                else {
                    dp[i][diff] = 1;
                }
                if (dp[j].count(diff)) {
                    dp[i][diff] += dp[j][diff];
                    ret += dp[j][diff];
                }
            }
        }
        return ret;
    }
};


int main() {
    freopen("in.txt", "r", stdin);
    vector<int> x;
    x.push_back(0);
    x.push_back(2000000000);
    x.push_back(-294967296);
    Solution a;
    cout << a.numberOfArithmeticSlices(x);
    return 0;
}
