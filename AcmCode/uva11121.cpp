#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 100006;

int value[MAX_NUMBER];
int number;

int main() {
	int test_case;
	scanf("%d", &test_case);
	int case_number = 1;
	while (test_case--) {
		int location = 0;
		scanf("%d", &number);
		int temp = number;
		int flag = 0;
		while (number) {
			value[location] = (number % (-2) + 2) % 2;
			location++;
			if (number > 0) {
				number /= -2;
			}
			else {
				number -= 1;
				number /= -2;
			}
		}
		printf("Case #%d: ", case_number);
		case_number++;
		if (temp != 0) {
			for (int i = location - 1; i >= 0; i--) {
				printf("%d", value[i]);
			}
			printf("\n");
		}
		else {
			printf("0\n");
		}
	}
	return 0;
}