#include <iostream> 
#include <cstring>
#include <stdio.h>
using namespace std;
const int MAX_NUM = 600;
const int MIN_PAGE = 10000000;
int temp_path[MAX_NUM];
int ans_path[MAX_NUM];
int pages[MAX_NUM];
int main() {
	freopen("input.txt","r",stdin);
	int test_case;
	cin >> test_case;
	while (test_case--) {
		memset(ans_path,0,sizeof(ans_path));
        memset(pages,0,sizeof(pages));
		memset(temp_path,0,sizeof(temp_path));
		int books, parts;
		cin >> books >> parts;
		long long max_sum = 0;
        long long min_page = 0;
		for (int i = 0; i < books; i++) {
			cin >> pages[i];
			max_sum += pages[i];
			if (pages[i] > min_page)
				min_page = pages[i];
		}
        long long minimized_num = max_sum;
        int ans_parts;
		while (min_page < max_sum) {
			long long mid = (min_page + max_sum) / 2;
			int k_parts = 0;
			int part_num = 0;
			long long sum_part = 0;
            memset(temp_path,0,sizeof(temp_path));
			for (int i = books - 1; i >= 0; i--) {
				if (sum_part + pages[i] > mid) {
					k_parts++;
					temp_path[i] = 1;
					sum_part = 0;
				}
				if (k_parts >= parts)
					break;
				sum_part += pages[i];
			}
			if (k_parts <= parts - 1 && mid < minimized_num) {
				memcpy(ans_path,temp_path,sizeof(temp_path));
                max_sum = mid;
                ans_parts = k_parts;
			}
            else {
				min_page = mid + 1;
			}
		}
        for (int i = 0; ans_parts < parts - 1 && i < books; i++) {
            if (ans_path[i] == 0) {
                ans_path[i] = 1;
                ans_parts++;
                }
            }
		for (int i = 0,part_num = 0; i< books; i++) {
			cout << pages[i];
            if (i != books -1) {
                cout << " ";
            }
			if (part_num < parts - 1 && ans_path[i]) {
				cout << "/ ";
			}
		}
		cout << endl;
	}
	return 0;
}
