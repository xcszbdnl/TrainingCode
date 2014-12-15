#include <cstdio>
#include <string.h>
#include <algorithm>

using namespace std;
const int MAX_NUMBER = 100005;

long long value[MAX_NUMBER];
long long sums[MAX_NUMBER];
long long ans;

long long gcd(long long a, long long b) {
	if (b == 0) {
		return a;
	}
	while (b) {
		long long c = b;
		b = a % b;
		a = c;
	}
	return a;
}

int main() {
	int number;
	scanf("%d", &number);
	memset(sums, 0, sizeof(sums));
	for (int i = 1; i <= number; i++) {
		scanf("%I64d", &value[i]);
	}
	sort(value + 1, value + 1 + number);
	for (int i = 1; i <= number; i++) {
		sums[i] = sums[i - 1] + value[i];
	}
	for (int i = 1; i < number; i++) {
		ans = ans + sums[number] - sums[i] - (number - i) * value[i];
	}
	ans = ans * 2;
	ans += sums[number];
	long long common = gcd(ans, number);
	printf("%I64d %I64d\n", ans / common, number / common);
	return 0;
}