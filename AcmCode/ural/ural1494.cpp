#include <cstdio>
#include <cstring>
#include <stack>

using namespace std;
const int maxn = 100007;
stack<int> s;
int in[maxn];
int main() {
//    freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &in[i]);
    }
    int cnt_loc = 1;
    for (int i = 1; i <= n; i++) {
        while (s.empty() || (s.top() != in[i] && cnt_loc <= in[i])) {
            s.push(cnt_loc);
            cnt_loc++;
        }
        if (s.top() == in[i]) {
            s.pop();
        }
    }
    if (!s.empty()) {
        printf("Cheater\n");
    }
    else {
        printf("Not a proof\n");
    }
    return 0;
}
