#include <cstdio>
#include <string.h>
#include <iostream>

using namespace std;

long long x, y, gcd_d;
int number;

int main() {
	scanf("%d", &number);
	int ans_7 = 0;
	for (int i = number / 7; i >= 0; i--) {
		if ((number - i * 7) % 4 == 0) {
			ans_7 = i;
			break;
		}
	}
	int flag = 0;
	if ((number - ans_7 * 7) % 4 != 0) {
		flag = 1;
		printf("-1\n");
	}
	else {
		int ans_4 = (number - ans_7 * 7) / 4;
		for (int i = 1; i <= ans_4; i++) {
			printf("%c", '0' + 4);
		}
		for (int i = 1; i <= ans_7; i++) {
			printf("%c", '0' + 7);
		}
		printf("\n");
	}
	return 0;
}