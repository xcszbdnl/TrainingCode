#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 70007;
struct Num {
    int num, order;
    bool operator < (const struct Num &a) const {
        if (num == a.num) {
            return order < a.order;
        }
        return num < a.num;
    }
};

struct Num input[maxn];
int n;

bool query(int left, int right, int x) {
    int low = 1;
    int high = n;
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (input[mid].num == x) {
            if (input[mid].order >= left && input[mid].order <= right) {
                return 1;
            }
            else if (input[mid].order < left) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        else if (input[mid].num > x) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return 0;
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &input[i].num);
        input[i].order = i;
    }
    sort(input + 1, input + 1 + n);
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int l, r, x;
        scanf("%d%d%d", &l, &r, &x);
        if (query(l, r, x)) {
            printf("1");
        }
        else {
            printf("0");
        }
    }
    printf("\n");
    return 0;
}
