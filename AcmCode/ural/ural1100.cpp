#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 150007;
struct Person {
    int order, id, m;
    bool operator < (const struct Person &a) const {
        if (m == a.m) {
            return order < a.order;
        }
        return m > a.m;
    }
};
int n;
struct Person person[maxn];
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &person[i].id, &person[i].m);
        person[i].order = i;
    }
    sort(person + 1, person + 1 + n);
    for (int i = 1; i <= n; i++) {
        printf("%d %d\n", person[i].id, person[i].m);
    }
    return 0;
}
