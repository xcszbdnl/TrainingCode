#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 60005;

int prime[MAX_NUMBER], factor[MAX_NUMBER];
int prime_number, number;

void getAllPrime() {
	prime_number = 1;
	prime[1] = 2;
	for (int i = 3; i < MAX_NUMBER; i++) {
		int j;
		for (j = 1; prime[j] * prime[j] <= i; j++) {
			if (i % prime[j] == 0) {
				break;
			}
		}
		if (prime[j] * prime[j] > i) {
			prime[++prime_number] = i;
		}
	}
}

int main() {
	getAllPrime();
	printf("PERFECTION OUTPUT\n");
	while (scanf("%d", &number) != EOF) {
		if (!number) {
			break;
		}
		memset(factor, 0, sizeof(factor));
		int temp = number;
		for (int i = 1; i <= prime_number; i++) {
			while(temp % prime[i] == 0) {
				factor[i]++;
				temp = temp / prime[i];
			}
		}
		long long ans = 1;
		for (int i = 1; i <= prime_number; i++) {
			int sums;
			if (factor[i] != 0) {
				sums = 0;
				int temp = 1;
				for (int j = 0; j <= factor[i]; j++) {
					sums += temp;
					temp = temp * prime[i];
				}
				ans = ans * sums;
			}
		}
		ans = ans - number;
		printf("%5d", number);
		if (ans == number) {
			printf("  PERFECT\n");
		}
		else if (ans < number) {
			printf("  DEFICIENT\n");
		}
		else {
			printf("  ABUNDANT\n");
		}
	}
	printf("END OF OUTPUT\n");
	return 0;
}