#include <cstdio>
#include <set>
#include <cstring>
#include <map>

using namespace std;
const int maxn = 1000007;
const long long mod = 1000 * 1000 * 1000 + 7;
typedef long long LL;

struct Point {
    LL x, y;
};
map<pair<LL,LL>, int> mp;
map<LL, int> mpx, mpy;
set<int> dx[maxn], dy[maxn];
set<int>::iterator it;
int fa[maxn], siz[maxn], block_num, x_num, y_num, tot;
int idx[maxn];
LL n, m, ans;
struct Point point[maxn];

int findFa(int x) {
    return x == fa[x] ? x : fa[x] = findFa(fa[x]);
}
int getX(LL x) {
    if (mpx.count(x)) {
        return mpx[x];
    }
    else {
        mpx[x] = ++x_num;
        return mpx[x];
    }
}

int getY(LL y) {
    if (mpy.count(y)) {
        return mpy[y];
    }
    else {
        mpy[y] = ++y_num;
        return y_num;
    }
}
void unionSet(int a, int b) {
    int x = findFa(a);
    int y = findFa(b);
    fa[y] = x;
    siz[x] += siz[y];
}
void addNode(int i, LL x, LL y) {
    pair<LL, LL> cnt_pair = make_pair(x, y);
    if (mp.count(cnt_pair)) {
        idx[i] = mp[cnt_pair];
        siz[findFa(idx[i])]++;
    }
    else {
        idx[i] = mp[cnt_pair] = ++tot;
        fa[tot] = tot;
        siz[tot] = 1;
        mp[cnt_pair] = tot;
        int cnt_x = getX(x);
        int cnt_y = getY(y);
        dx[cnt_x].insert(tot);
        dy[cnt_y].insert(tot);
        point[tot].x = x;
        point[tot].y = y;
    }
}

void delNode(int i) {
    int block = findFa(idx[i]);
    LL x = point[block].x;
    LL y = point[block].y;
    siz[block]--;
    if (siz[block] == 0) {
        mp.erase(make_pair(x, y));
        int cnt_x = getX(x);
        int cnt_y = getY(y);
        dx[cnt_x].erase(block);
        dy[cnt_y].erase(block);
    }
}

void query(int i) {
    int block = findFa(idx[i]);
    LL x = point[block].x;
    LL y = point[block].y;
    int cnt_x = getX(x);
    int cnt_y = getY(y);
    for (it = dx[cnt_x].begin(); it != dx[cnt_x].end(); ) {
        if (*it == block) {
            it++;
            continue;
        }
        LL next_y = point[*it].y;
        ans = ((ans + ((((next_y - y) % mod) * ((next_y - y) % mod)) % mod) * siz[*it]) % mod + mod) % mod;
        unionSet(block, *it);
        dx[cnt_x].erase(it++);
        dy[cnt_y].erase(*it);
    }
    for (it = dy[cnt_y].begin(); it != dy[cnt_y].end();) {
        if (*it == block) {
            it++;
            continue;
        }
        LL next_x = point[*it].x;
        ans = ((ans + ((((x - next_x) % mod) * ((x - next_x) % mod)) % mod) * siz[*it]) % mod + mod) % mod;
        unionSet(block, *it);
        dy[cnt_y].erase(it++);
    }
}

void update(char *temp, int i, LL d) {
    int a = findFa(idx[i]);
    LL x = point[a].x;
    LL y = point[a].y;
    if (temp[0] == 'U') {
        x -= d;
    }
    else if (temp[0] == 'D') {
        x += d;
    }
    else if (temp[0] == 'L') {
        y -= d;
    }
    else {
        y += d;
    }
    delNode(i);
    addNode(i, x, y);
}
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%I64d%I64d", &n, &m) != EOF) {
        mp.clear();
        mpx.clear();
        mpy.clear();
        block_num = x_num = y_num = tot = 0;
        for (int i = 1; i <= n; i++) {
            LL x, y;
            scanf("%I64d%I64d", &x, &y);
            addNode(i, x, y);
        }
        int t;
        scanf("%d", &t);
        LL lastans = 0;
        for (int i = 1; i <= t; i++) {
            char temp[10];
            scanf("%s", temp);
            if (temp[0] == 'Q') {
                LL cnt_n;
                scanf("%I64d", &cnt_n);
                cnt_n ^= lastans;
                ans = 0;
                query(cnt_n);
                printf("%I64d\n", ans);
                lastans = ans;
            }
            else {
                LL cnt_n, d;
                scanf("%I64d%I64d", &cnt_n, &d);
                cnt_n ^= lastans;
                update(temp, cnt_n, d);
            }
        }
        for (int i = 0; i <= x_num; i++) {
            dx[i].clear();
        }
        for (int i = 0; i <= y_num; i++) {
            dy[i].clear();
        }
    }
    return 0;
}
