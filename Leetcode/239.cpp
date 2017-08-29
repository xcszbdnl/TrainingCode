#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> result, que(n, 0);
        int front = 1, rear = 0;
        for (int i = 0; i < n; i++) {
            while (rear >= front && nums[que[rear]] < nums[i]) {
                rear--;
            }
            rear++;
            que[rear] = i;
            while (rear >= front && que[rear] - que[front] + 1 > k) {
                front++;
            }
            if (i >= k - 1) {
//                printf("%d\n", que[front]);
                result.push_back(nums[que[front]]);
            }
        }
        return result;
    }
};

int main() {
}
