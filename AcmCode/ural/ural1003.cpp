#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;
const int maxn = 5007;

struct Seg {
    int left, right, type;
};
struct Seg seg[maxn];
int father[maxn], r[maxn], ar[maxn], length, cnt;
map<int, int> maps;

void init() {
    length = 1;
    for (int i = 2; i <= cnt; i++) {
        if (ar[i] != ar[i - 1]) {
            length++;
            ar[length] = ar[i];
        }
    }
}

int find(int x) {
    if (x == father[x]) {
        return x;
    }
    else {
        int t = father[x];
        father[x] = find(father[x]);
        r[x] = (r[x] + r[t]) % 2;
        return father[x];
    }
}

int binarySearch(int a) {
    int low = 1;
    int high = length;
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (ar[mid] == a) {
            return mid;
        }
        else if (ar[mid] > a) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return -1;
}

void union_set(int a, int b, int type) {
    int x = find(a);
    int y = find(b);
    father[y] = x;
    r[y] = (r[a] + type + 2 - r[b]) % 2;
}
int main() {
//    freopen("input.txt", "r", stdin);
    while (scanf("%d", &length) != EOF) {
        if (length == -1) {
            break;
        }
        int m;
        scanf("%d", &m);
        maps.clear();
        cnt = 0;
        int flag = 0;
        int s_m = m;
        for (int i = 1; i <= m; i++) {
            int a, b;
            char even[30];
            scanf("%d%d%s", &a, &b, even);
            if (!flag && (a > length || b > length)) {
                flag = 1;
                s_m = i - 1;
            }
            ar[++cnt] = a - 1;
            ar[++cnt] = b;
            seg[i].left = a - 1;
            seg[i].right = b;
            if (even[0] == 'e') {
                seg[i].type = 0;
            }
            else {
                seg[i].type = 1;
            }
        }
        sort(ar + 1, ar + 1 + cnt);
        init();
        int ans = 0;
        for (int i = 1; i <= length; i++) {
            father[i] = i;
            r[i] = 0;
        }
        for (int i = 1; i <= m && i <= s_m; i++) {
            int left = binarySearch(seg[i].left);
            int right = binarySearch(seg[i].right);
            int x = find(left);
            int y = find(right);
            if (x == y) {
                if (seg[i].type == 0 && r[left] != r[right]) {
                    break;
                }
                else if (seg[i].type == 1 && (r[left] + r[right]) != 1) {
                    break;
                }
            }
            else {
                union_set(left, right, seg[i].type);
            }
            ans = i;
        }
        printf("%d\n", ans);
    }
}
