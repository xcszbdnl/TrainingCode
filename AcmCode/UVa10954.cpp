#include <stdio.h>
#include <iostream>
#include <cstring>
using namespace std;
const int MAX_NUM = 5050;
int integers[MAX_NUM];
int integer_num;
void min_heap(int i) {
	int left = i * 2;
	int right = i * 2 + 1;
	int min;
	if (left <= integer_num && integers[left] < integers[i]) {
		min = left;
	} else {
		min =i;
	}
	if (right <= integer_num && integers[right] < integers[min]) {
		min =right;
	}
	if (min != i) {
		int temp = integers[i];
		integers[i] = integers[min];
		integers[min] = temp;
		min_heap(min);
	}
}
void build_heap() {
	for (int i = integer_num / 2; i >= 1; i--) {
		min_heap(i);
	}
}
void insert_heap(int num) {
	int i;
	for (i = ++integer_num; integers[i / 2] > num; i /= 2) {
		integers[i] = integers[i / 2];
	}
	integers[i] = num;
}
int delete_min() {
	int min_element, last_element;
	min_element = integers[1];
	last_element = integers[integer_num--];
	int child;
	int i;
	for (i = 1; i * 2 <= integer_num; i =child) {
		child = i * 2;
		if (child < integer_num && integers[child+1] < integers[child])
			child++;
		if (last_element > integers[child]) {
			integers[i] = integers[child];
		} else 
			break;
	}
	integers[i] = last_element;
	return min_element;
}
int main()
{
	freopen("input.txt","r",stdin);
	while (cin >> integer_num) {
		if (!integer_num) {
			break;
		}
		memset(integers,0,sizeof(integers));
		for (int i = 1; i <= integer_num; i++) {
			cin >> integers[i];
		}
		build_heap();
		int sum = 0;
		while (integer_num != 1) {
			int min_num_1;
			int min_num_2;
			int add_num;
			min_num_1 = delete_min();
			min_num_2 = delete_min();
			add_num = min_num_1 + min_num_2;
			sum += add_num;
			insert_heap(add_num);
		}
		cout << sum << endl;
	}
	return 0;
}
