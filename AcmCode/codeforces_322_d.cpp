#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Ret {
  int x, y;
};

struct Ret ret[5];

int main() {
  //freopen("in.txt", "r", stdin);
  int square = 0;
  for (int i = 1; i <= 3; i++) {
    scanf("%d%d", &ret[i].x, &ret[i].y);
    if (ret[i].x > ret[i].y) {
      swap(ret[i].x, ret[i].y);
    }
    square += ret[i].x * ret[i].y;
  }
  int flag = 0;
  int len = 0;
  for (int i = 1; i <= square; i++) {
    if (i * i == square) {
      flag = 1;
      len = i;
    }
  }
  if (!flag) {
    printf("-1\n");
    return 0;
  }
  if (ret[1].y == ret[2].y && ret[1].y == ret[3].y && ret[1].x + ret[2].x + ret[3].x == ret[1].y) {
    printf("%d\n", len);
    for (int k = 1; k <= 3; k++) {
      for (int i = 1; i <= ret[k].x; i++) {
        for (int j = 1; j <= ret[k].y; j++) {
          printf("%c", 'A' + k - 1);
        }
        printf("\n");
      }
    }
    return 0;
  }
  flag = 0;
  int num = 0;
  for (int i = 1; i <= 3; i++) {
    if (ret[i].y == len) {
      flag = 1;
      num = i;
      break;
    }
  }
  if (!flag) {
    printf("-1\n");
    return 0;
  }
  printf("%d\n", len);
  for (int i = 1; i <= 3; i++) {
    if (i != num) {
      int side_1, side_2;
      if (ret[i].x + ret[num].x == len) {
        side_1 = ret[i].y;
        side_2 = ret[i].x;
      }
      else {
        side_1 = ret[i].x;
        side_2 = ret[i].y;
      }
      for (int k = 1; k <= side_1; k++) {
        for (int j = 1; j <= side_2; j++) {
          printf("%c", 'A' + i - 1);
        }
        for (int j = 1; j <= ret[num].x; j++) {
          printf("%c", 'A' + num - 1);
        }
        printf("\n");
      }
    }
  }
  return 0;
}

