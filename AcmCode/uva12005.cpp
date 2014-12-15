#include <cstdio>
#include <string.h>
#include <cmath>

const int MAX_NUMBER = 20000000;
const int MAX_PRIME = 2000000;
bool vis[MAX_NUMBER + 3];
int prime[MAX_PRIME];
int prime_number;
long long number;

void getAllPrime() {
	memset(vis, 0, sizeof(vis));
	vis[0] = vis[1] = true;
	prime_number = 0;
	for (int i = 2; i <= MAX_NUMBER; i++) {
		if (!vis[i]) {
			prime[prime_number] = i;
			prime_number++;
		}
		for (int j = 0; prime[j] * i <= MAX_NUMBER;j++)
		{
			vis[prime[j] * i]=true;//É¸µôËØÊý±¶Êý
			if((i % prime[j]) == 0) {
				break;
			}
		}
	}
}

long long calculate(long long cnt_number) {
	int i = 0;
	long long ans = 1;
	while (prime[i] * prime[i] <= cnt_number && i < prime_number) {
		int sums = 1;
		while (cnt_number % prime[i] == 0) {
			sums++;
			cnt_number /= prime[i];
		}
		i++;
		ans = ans * sums;
	}
	if (cnt_number != 1) {
		ans = ans * 2;
	}
	return ans;
}

int main() {
	getAllPrime();
	while (scanf("%lld", &number) != EOF) {
		if (!number) {
			break;
		}
		long long ans = calculate(4 * number - 3);
		printf("%lld %lld\n", number, ans);
	}
	return 0;
}