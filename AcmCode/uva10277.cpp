#include <cstdio>
#include <string.h>
#include <cmath>

double eps = 1e-10;
using namespace std;
unsigned long long p, q;

unsigned long long gcd(unsigned long long a, unsigned long long b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a % b);
}

int main() {
	while (scanf("%llu%llu", &p, &q) != EOF) {
		if (!p && !q) {
			break;
		}
		if (p == 0) {
			printf("0 2\n");
			continue;
		}
		unsigned long long k = gcd(p, q);
		unsigned long long p_1, q_1;
		p_1 = p / k;
		q_1 = q / k;
		int flag = 0;
		unsigned long long ans_a, ans_b;
		for (int i = 2; i < 50000; i++) {
			unsigned long long temp = i * (i - 1);
			if (temp % p_1 == 0) {
				unsigned long long s = temp * 4 * q_1 / p_1 + 1;
				unsigned long long sqrt_s = (unsigned long long)sqrt(s + eps);
				if (sqrt_s * sqrt_s != s) {
 					continue;
				}
				sqrt_s++;
				if (sqrt_s % 2 == 0) {
					flag = 1;
					ans_a = i;
					ans_b = sqrt_s / 2 - i;
					break;
				}
			}
		}
		if (flag) {
			printf("%llu %llu\n", ans_a, ans_b);
		}
		else {
			printf("impossible\n");
		}
	}
	return 0;
}


