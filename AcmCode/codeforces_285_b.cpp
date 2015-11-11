#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <iostream>

using namespace std;
const int maxn = 10007;

map<string, string> maps;
map<string, int> num;
map<string, string> ans;
map<string, int>::iterator it1;
map<string, string>::iterator it2;
int degree[maxn];
int n;
int main() {
  //freopen("in.txt", "r", stdin);
  memset(degree, 0, sizeof(degree));
  scanf("%d", &n);
  int cnt = 0;
  while (n--) {
    string a, b;
    cin >> a >> b;
    if (!num.count(a)) {
      num[a] = ++cnt;
    }
    if (!num.count(b)) {
      num[b] = ++cnt;
    }
    degree[num[b]]++;
    maps[a] = b;
  }
  for (it1 = num.begin(); it1 != num.end(); it1++) {
    int b = it1->second;
    string cnt = it1->first;
    if (!degree[b]) {
      if (!maps.count(cnt)) {
        continue;
      }
      else {
        while (maps.count(cnt)) {
          cnt = maps[cnt];
        }
        ans[it1->first] = cnt;
      }
    }
  }
  printf("%d\n", ans.size());
  for (it2 = ans.begin(); it2 != ans.end(); it2++) {
    cout << it2->first << " " << it2->second << endl;
  }
  return 0;
}
