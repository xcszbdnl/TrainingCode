#include <cstdio>
#include <set>

using namespace std;

set<int> s;
set<int>::iterator it;
int vis[100000];
int main() {
    s.insert(0);
    s.insert(1);
    s.insert(2);
    vis[0] = vis[1] = vis[2] = 1;
    for (it = s.begin(); it != s.end();) {
        for (int i = 0; i < 30; i++) {
            if (!vis[i]) {
                vis[i] = 1;
                s.insert(i);
                break;
            }
        }
        it++;
    }
    for (it = s.begin(); it != s.end(); it++) {
        printf("%d\n", *it);
    }
    return 0;
}
