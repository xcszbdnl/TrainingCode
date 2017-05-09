#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> temp;
        if (nums1.size() == 0) {
            int m = nums2.size();
            if ((m % 2) == 1) {
                return nums2[m / 2];
            }
            else {
                return (nums2[m / 2] + nums2[m / 2 - 1]) / 2.0;
            }
        }
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        int n = nums1.size();
        int m = nums2.size();
        int j = (n + m + 1) / 2 - 0;
        int left_max, right_min;
        if (nums2[j - 1] <= nums1[0]) {
            left_max = nums2[j - 1];
            if (m == n) {
                right_min = nums1[0];
            }
            else {
                right_min = min(nums1[0], nums2[j]);
            }
            if (((n + m) % 2) == 1) {
                return left_max;
            }
            return (left_max + right_min) / 2.0;
        }
        j = (n + m + 1) / 2 - n;
        if (nums1[n - 1] <= nums2[j]) {
            if (n == m) {
                left_max = nums1[n - 1];
            }
            else {
                left_max = max(nums1[n - 1], nums2[j - 1]);
            }
            right_min = nums2[j];
            if (((n + m) % 2) == 1) {
                return left_max;
            }
            return (left_max + right_min) / 2.0;
        }
        int low = 1;
        int high = n - 1;
        int mid;
        while (low <= high) {
            mid = (low + high) >> 1;
            j = (n + m + 1) / 2 - mid;
            if (nums1[mid - 1] <= nums2[j] && nums2[j - 1] <= nums1[mid]) {
                break;
            }
            if (nums1[mid - 1] > nums2[j]) {
                high = mid - 1;
            }
            if (nums2[j - 1] > nums1[mid]) {
                low = mid + 1;
            }
        }
        left_max = max(nums1[mid - 1], nums2[j - 1]);
        right_min = min(nums1[mid], nums2[j]);
        if (((n + m) % 2) == 1) {
            return left_max;
        }
        return (left_max + right_min) / 2.0;
    }
};

int main() {
    freopen("in.txt", "r", stdin);
    vector<int> nums1, nums2;
    int n1, n2;
    scanf("%d%d", &n1, &n2);
    int num;
    for (int i = 0; i < n1; i++) {
        scanf("%d", &num);
        nums1.push_back(num);
        //printf("%d\n", num);
    }
    for (int i = 0; i < n2; i++) {
        scanf("%d", &num);
        nums2.push_back(num);
    }
    Solution a;
    double result = a.findMedianSortedArrays(nums1, nums2);
    printf("%.1f\n", result);
    return 0;
}
