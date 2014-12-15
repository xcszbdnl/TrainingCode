#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 40000;

int prime[MAX_NUMBER], value[MAX_NUMBER];
char input[MAX_NUMBER];
int prime_number;
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
	while (1) {
		memset(value, 0, sizeof(value));
		gets(input);
		if (input[0] == '0') {
			break;
		}
		int length = strlen(input);
		input[length] = ' ';
		input[length + 1] = '\0';
		int number = 0;
		int temp, result = 1;
		int power= 0;
		int flag = 0;
		for (int i = 0; input[i]; i++) {
			if (input[i] != ' ') {
				number = number * 10 + input[i] - '0';
			}
			else if (input[i] == ' ') {
				if (flag == 0) {
					flag = 1;
					temp = number;
					flag = 1;
					number = 0;
				}
				else {
					for (int i = 1; i <= number; i++) {
						result = result * temp;
					}
					flag = 0;
					number = 0;
				}
			}
		}
		int max_loc, first, min_loc;
		first = 1;
		result = result - 1;
		for (int i = 1; i <= prime_number; i++) {
			while (result % prime[i] == 0) {
				value[i]++;
				result = result / prime[i];
				if (first) {
					min_loc = max_loc = i;
					first = 0;
				}
				else {
					max_loc = i;
				}
			}
		}
		first = 1;
		for (int i = max_loc; i >= min_loc; i--) {
			if (first && value[i] != 0) {
				printf("%d %d", prime[i], value[i]);
				first = 0;
			}
			else if (value[i] != 0) {
				printf(" %d %d", prime[i], value[i]);
			}
		}
		printf("\n");
	}
	return 0;
}