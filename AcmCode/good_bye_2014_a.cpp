#include <cstdio>
#include <cstring>


const int maxn = 30007;


int a[maxn];
int n, t;
int main() {
  //freopen("in.txt", "r", stdin);
  scanf("%d%d", &n, &t);
  for (int i = 1; i <= n - 1; i++) {
    scanf("%d", &a[i]);
  }
  a[n] = 1;
  int cnt = 1;
  int flag = 0;
  while (cnt <= n) {
    if (cnt == t) {
      flag = 1;
      break;
    }
    cnt = cnt + a[cnt];
  }
  if (flag) {
    printf("YES\n");
  }
  else {
    printf("NO\n");
  }
  return 0;
}
