#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:

    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long long> sums(n + 4, 0);
        vector<int> trees(n + 4, 0);
        vector<long long> sum_num;
        sum_num.push_back(0);
        for (int i = 1; i <= n; i++) {
            sums[i] = sums[i - 1] + nums[i - 1];
//            cout << nums[i - 1] << " " << sums[i] << endl;
            sum_num.push_back(sums[i]);
//            cout << sum_num[i] << endl;
        }
        sort(sum_num.begin(), sum_num.end());
        vector<long long>::iterator it = unique(sum_num.begin(), sum_num.end());
        sum_num.erase(it, sum_num.end());
//        for (int i = 0; i < sum_num.size(); i++) {
//            cout << sum_num[i] << endl;
//        }
        int idx = bi_search(sum_num, 0);
//        cout << idx << endl;
        update(trees, idx, 1);
        int result = 0;
        for (int i = 1; i <= n; i++) {
//            cout << sums[i] << endl;
            long long cnt_upper = sums[i] - lower;
            long long cnt_lower = sums[i] - upper;
            idx = bi_search(sum_num, cnt_upper);
            int sum_1 = count_sum(trees, idx);
            idx = bi_search(sum_num, cnt_lower - 1);
            int sum_2 = count_sum(trees, idx);
            result += (sum_1 - sum_2);
            idx = bi_search(sum_num, sums[i]);
//            for (int i = 0; i <= n; i++) {
//                cout << "tree:" << trees[i] << endl;
//            }
            update(trees, idx, 1);
        }
        return result;
    }

    int bi_search(vector<long long> & sum_num, long long x) {
        int n = sum_num.size();
        if (x < sum_num[0]) {
            return 0;
        }
        int low = 0;
        int high = n - 1;
        while (low <= high) {
            int mid = (low + high) >> 1;
            if (sum_num[mid] > x) {
                high = mid - 1;
            }
            else if (sum_num[mid] < x) {
                low = mid + 1;
            }
            else {
                return mid + 1;
            }
        }
        return high + 1;
    }

    void update(vector<int> &trees, int idx, int v) {
        int n = trees.size();
        while (idx <= n) {
            trees[idx] += v;
            idx += lowbit(idx);
        }
    }

    int count_sum(vector<int> &trees, int idx) {
        int r = 0;
        while (idx > 0) {
            r += trees[idx];
            idx -= lowbit(idx);
        }
        return r;
    }

    int lowbit(int x) {
        return x & (-x);
    }
};

int main() {
    freopen("in.txt", "r", stdin);
    int n, lower, upper;
    scanf("%d%d%d", &n, &lower, &upper);
    vector<int> num;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        num.push_back(x);
    }
    Solution a;
    printf("xcs%d\n", a.countRangeSum(num, lower, upper));
}
