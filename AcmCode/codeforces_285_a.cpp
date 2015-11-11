#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10007;
int a, b, c, d;
int main() {
  //freopen("in.txt", "r", stdin);
  scanf("%d%d%d%d", &a, &b, &c, &d);
  int num_1 = max(3 * a / 10, a - a / 250 * c);
  int num_2 = max(3 * b / 10, b - b / 250 * d);
  if (num_1 == num_2) {
    printf("Tie\n");
  }
  else if (num_1 > num_2) {
    printf("Misha\n");
  }
  else {
    printf("Vasya\n");
  }
  return 0;
}
