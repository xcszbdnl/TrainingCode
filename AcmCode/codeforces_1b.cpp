#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 50000;
int number, ans[MAX_NUMBER];
char input[MAX_NUMBER];
char output[MAX_NUMBER];
int row, column, length;
void dealSystem1() {
	int row = 0, column = 0;
	int column_start = 0;
	for (int i = 1; input[i]; i++) {
		if (input[i] == 'C') {
			column_start = 1;
		}
		else if (column_start) {
			column = column * 10 + input[i] - '0';
		}
		else {
			row = row * 10 + input[i] - '0';
		}
	}
	int big;
	for (big = 1; column >= ans[big]; big++) {
		column -= ans[big];
	}
	column--;
	for (int i = 0; i < big; i++) {
		output[i] = 'A' + column / (ans[big - i - 1]);
		column = (column % ans[big - i - 1]);
	}
	output[big] = '\0';
	printf("%s%d\n", output, row);
}

void dealSystem2() {
	int char_length;
	int first = 0;
	for (int i = 0; input[i]; i++) {
		if (input[i] >= '0' && input[i] <= '9') {
			if (!first) {
				char_length = i;
				first = 1;
			}
			row = row * 10 + input[i] - '0';
		}
	}
	column = 0;
	for (int i = 0; i < char_length; i++) {
		column = column + (input[i] - 'A') * ans[char_length - 1 - i];
	}
	column++;
	for (int i = 1; i < char_length; i++) {
		column += ans[i];
	}
	printf("R%dC%d\n", row, column);
}

int main() {
	scanf("%d", &number);
	ans[0] = 1;
	ans[1] = 26;
	int i = 2;
	int power = 26;
	while (power < 1000000) {
		ans[i] = ans[i -1] * 26;
		power = ans[i];
		i++;
	}
	while (number--) {
		scanf("%s", input);
		for (int i = 0; i < 300; i++) {
			output[i] = 'A';
		}
		int flag = 0, found = 0;
		if (input[0] == 'R') {
			length = strlen(input);
			for (int i = length - 1; i >= 0; i--) {
				if (input[i] == 'C') {
					found = i;
					break;
				}
			}
			for (int i = 1; i <= found; i++) {
				if (input[i] >= '0' && input[i] <= '9') {
					flag = 1;
					break;
				}
			}
			if (flag) {
				dealSystem1();
			}
			else {
				dealSystem2();
			}
		}
		else {
			dealSystem2();
		}
	}
	return 0;
}