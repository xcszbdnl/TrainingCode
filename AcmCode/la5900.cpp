#include <cstdio>
#include <string.h>
#include <cmath>
#include <algorithm>

using namespace std;
const int MAX_NUMBER = 100006;
long long number;

struct Node {
	long long n;
	long long k;
};

bool cmp(Node a, Node b) {
	if (a.n == b.n) {
		return a.k < b.k;
	}
	else {
		return a.n < b.n;
	}
}

struct Node ans[MAX_NUMBER];
int ans_number;

long long getCom(long long k, long long n) {
	long long result = 1;
	for (long long i = 1; i <= k; i++) {
		result = result * (n - i + 1) / i;
	}
	return result;
}

void addAns(long long k, long long n) {
	ans_number++;
	ans[ans_number].k = k;
	ans[ans_number].n = n;

	ans_number++;
	ans[ans_number].k = n - k;
	ans[ans_number].n = n;
}


int main() {
	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		scanf("%lld", &number);
		ans_number = 0;
		addAns(1, number);
		long long n = (long long)sqrt(2 * number + 0.5);
		n++;
		if (getCom(2, n) == number) {
			addAns(2, n);
		}
		n = (long long)pow(6 * number + 0.5, 1.0 / 3);
		n += 2;
		if (getCom(3, n) == number) {
			addAns(3, n);
		}
		for (n = 4; n <= 10000; n++) {
			for (long long k = 4; k <= n / 2; k++) {
				long long temp = getCom(k, n);
				if (temp > number) {
					break;
				}
				if (temp == number) {
					addAns(k, n);
					break;
				}
			}
		}
		long long real_ans = 1;
		sort(ans + 1, ans + 1 + ans_number, cmp);
		for (int i = 2; i <= ans_number; i++) {
			if (ans[i].k != ans[i - 1].k || ans[i].n != ans[i - 1].n) {
				real_ans++;
			}
		}
		printf("%lld\n", real_ans);
		for (int i = 1; i <= ans_number; i++) {
			if (i == 1) {
				printf("(%lld,%lld)", ans[i].n, ans[i].k);
			}
			else if (ans[i].k != ans[i - 1].k || ans[i].n != ans[i - 1].n) {
				printf(" (%lld,%lld)", ans[i].n, ans[i].k);
			}
		}
		printf("\n");
	}
	return 0;
}