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
    int findIntegers(int num) {
        long long dp[64][2];
        dp[0][0] = 1;
        dp[0][1] = 1;
        dp[1][0] = 1;
        dp[1][1] = 1;
        int bit_mask[64] = {0};
        int bit_num = 0;
        long long ans = 0;
        bit_num = 1;
        bit_mask[0] = 1;
        while (num) {
            bit_mask[bit_num++] = num % 2;
            dp[bit_num][0] = dp[bit_num - 1][0] + dp[bit_num - 1][1];
            dp[bit_num][1] = dp[bit_num - 1][0];
            num /= 2;
        }
        int temp = 0;
        for (int i = bit_num - 1; i >= 0; i--) {
            if (bit_mask[i] == 0) {
                continue;
            }
            else {
                ans += dp[i][0];
                cout << ans << endl;
                if (bit_mask[i + 1] == 1) {
                    temp = 1;
                    break;
                }
            }
        }
//        int flag = 0;
//        for (int i = bit_num - 1; i >= 0; i--) {
//            if (flag == 0 && bit_mask[i] == 1) {
//                flag = 1;
//            }
//            else {
//                flag = 0;
//            }
//        }
//        if (flag && !temp) {
//            ans++;
//        }
        return ans;
    }
};



int main() {
    freopen("in.txt", "r", stdin);
    Solution a;
    cout << a.findIntegers(10) << endl;
    return 0;
}
