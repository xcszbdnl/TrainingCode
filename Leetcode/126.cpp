#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }
        int result = getReversePairs(nums, 0, nums.size());
        return result;
    }

    int getReversePairs(vector<int> &nums, int s, int e) {
        int mid = (s + e) >> 1;
        if (s + 1 == e) {
            return 0;
        }
        else {
            int left = getReversePairs(nums, s, mid);
            int right = getReversePairs(nums, mid, e);
            int cross_num = countCross(nums, s, e);
            return left + right + cross_num;
        }
    }

    int countCross(vector<int> &nums, int s, int e) {
        vector<int> temp;
        int mid = (s + e) >> 1;
        int i = s;
        int j = mid;
        int two_point = i;
        int ans = 0;
        while (i < mid || j < e) {
            while (two_point < mid && j < e && (long long)nums[two_point] <= (long long)2 * nums[j]) {
                two_point++;
            }
            if (i < mid && (j >= e || nums[i] < nums[j])) {
                temp.push_back(nums[i]);
                i++;
            }
            else {
                ans += mid - two_point;
                temp.push_back(nums[j]);
                j++;
            }
        }
        for (int i = s; i < e; i++) {
            nums[i] = temp[i - s];
        }
        return ans;
    }
};

int main() {
    freopen("in.txt", "r", stdin);
    vector<int> k;
    int cnt_num;

    while (scanf("%d", &cnt_num) != EOF) {
        k.push_back(cnt_num);
        //printf("%d ", cnt_num);
    }

    for (int i = 0; i < k.size(); i++) {
        printf("%d ", k[i]);
    }
    printf("\n");
    Solution a;
    printf("%d\n", a.reversePairs(k));
    for (int i = 0; i < k.size(); i++) {
        printf("%d ", k[i]);
    }
    printf("\n");
    return 0;
}
