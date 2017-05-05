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
    int jump(vector<int>& nums) {
        vector<int> dp(nums.size() + 1, -1);
        dp[0] = 0;
        int next_loc = 1;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = next_loc; j <= i + nums[i]; j++) {
                if (j >= nums.size()) {
                    break;
                }
                if (dp[j] == -1 || dp[j] > dp[i] + 1) {
                    dp[j] = dp[i] + 1;
                }
            }
            if (next_loc < i + nums[i]) {
                next_loc = i + nums[i];
            }
        }
        return dp[nums.size() - 1];
    }
};


int main() {
    freopen("in.txt", "r", stdin);
    Solution a;
    return 0;
}
