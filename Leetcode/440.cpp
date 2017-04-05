#include <cstdio>
#include <cstring>
#include <algorithm>


using namespace std;

class Solution {
public:
    int findKthNumber(int n, int k) {
        long long cnt_node = 1;
        k -= 1;
        while (k) {
            long long steps = calStep(cnt_node, cnt_node + 1, n);
            if (steps <= k) {
                cnt_node += 1;
                k -= steps;
            }
            else {
                cnt_node *= 10;
                k -= 1;
            }
        }
        return cnt_node;
    }

    int min(long long a, long long b) {
        return a < b ? a : b;
    }

    int calStep(long long n1, long long n2, int n) {
        long long steps = 0;
        while (n1 <= n) {
            steps += min(n + 1, n2) - n1;
            n1 *= 10;
            n2 *= 10;
        }
        return steps;
    }
};

int main() {
    Solution a;
    int r = a.findKthNumber(13, 2);
    printf("%d\n", r);
    return 0;
}
