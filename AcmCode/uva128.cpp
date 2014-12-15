#include <cstdio>
#include <string.h>

const int mod_number = 34943;
const int MAX_LENGTH = 1050;

char hex[20] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
char message[MAX_LENGTH];

long long getMod(int a, int power) {
	if (power == 0) {
		return 1;
	}
	long long x = getMod(a, power / 2);
	x = (x * x) % mod_number;
	if (power % 2 == 1) {
		x = (x * a) % mod_number;
	}
	return x;
}

int main() {
	while (1) {
		int base = 16;
		gets(message);
		if (message[0] == '#') {
			break;
		}
		int length = strlen(message);
		int ans = 0;
		for (int i = length - 1; i >= 0; i--) {
			int temp = getMod(2, base);
			temp = (message[i] * temp) % mod_number;
			ans = (ans + temp) % mod_number;
			base += 8;
		}
		int result = (mod_number - ans) % mod_number;
		for (int i = 3; i >= 0; i--) {
			int number = 0;
			for (int j = 0; j < 4; j++) {
				if (result & (1 << (i * 4 + j))) {
					number = number + (1 << j);
				}
			}
			if (i == 1) {
				printf(" ");
			}
			printf("%c", hex[number]);
		}
		printf("\n");
	}
	return 0;
}