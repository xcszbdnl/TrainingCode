#include <cstdio>
#include <string.h>
#include <algorithm>

using namespace std;

const int MAX_NUMBER = 1005;

struct Object {
	int value_1;
	int value_2;
};

bool cmp(struct Object a, struct Object b) {
	if (a.value_1 != b.value_1) {
		return a.value_1 > b.value_2;
	}
	else {
		return a.value_2 < b.value_2;
	}
}
struct Object object[MAX_NUMBER];
int people;

int main() {
	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		scanf("%d", &people);
		for (int i = 1; i <= people; i++) {
			scanf("%d%d", &object[i].value_1, &object[i].value_2);
		}
		sort(object + 1, object + 1 + people, cmp);

	}
}