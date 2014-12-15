#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <string.h>
#include <ctime>
#include <map>
using namespace std;
const int MAX_NUMBER = 1005;
const long long INF = 1000000000000ll;
#define min(a,b) ((a) > (b)) ? (b) : (a)
struct Point {
	int type;
	int order;
	long long price;
	long long quality;
	bool operator < (const Point &a) const {
		return quality > a.quality;
	}
};

struct Object {
	long long price;
	long long quality;
	bool operator < (const Object &a) const {
		if (price != a.price) {
			return price < a.price;
		}
		else {
			return quality < a.quality;
		}
	}
};
struct Com {
	int number;
	struct Object object[MAX_NUMBER];
};

struct Input {
	int id;
	long long price;
	long long quality;
	bool operator < (const struct Input &a) const {
		return id < a.id;
	}
};

struct Input input[MAX_NUMBER];
map<string, int> maps;
priority_queue<Point> buy;
struct Com com[MAX_NUMBER];
long long total;
int type_number, total_type, type_id;

int main() {
	int test_case;
	clock_t start = clock();
	scanf("%d", &test_case);
	while (test_case--) {
		long long min_q = INF;
		while (!buy.empty()) {
			buy.pop();
		}
		type_id = 0;
		maps.clear();
		memset(com, 0, sizeof(com));
		scanf("%d%I64d", &type_number, &total);
		string temp;
		for (int i = 1; i <= type_number; i++) {
			string cnt_type, temp;
			cin >> cnt_type >> temp >> input[i].price >> input[i].quality;
			if (maps[cnt_type]) {
				input[i].id = maps[cnt_type];
			}
			else {
				maps[cnt_type] = ++type_id;
				input[i].id = type_id;
			}
		}
		sort(input + 1, input + 1 + type_number);
		int previous_type = 1;
		com[1].object[1].price = input[1].price;
		com[1].object[1].quality = input[1].quality;
		com[1].number = 1;
		total_type = 1;
		for (int i = 2; i <= type_number; i++) {
			if (input[i - 1].id == input[i].id) {
				com[previous_type].number++;
				int cnt_number = com[previous_type].number;
				com[previous_type].object[cnt_number].price = input[i].price;
				com[previous_type].object[cnt_number].quality = input[i].quality;
			}
			else {
				total_type++;
				previous_type = total_type;
				com[total_type].number = 1;
				com[total_type].object[1].price = input[i].price;
				com[total_type].object[1].quality = input[i].quality;
			}
		}
		for (int i = 1; i <= total_type; i++) {
			sort(com[i].object + 1, com[i].object + 1 + com[i].number);
		}
		for (int i = 1; i <= total_type; i++) {
			struct Point point_buy;
			point_buy.order = 1;
			point_buy.type = i;
			point_buy.price = com[i].object[1].price;
			point_buy.quality = com[i].object[1].quality;
			buy.push(point_buy);
			total -= point_buy.price;
		}
		while (total > 0) {
			struct Point cnt_com = buy.top();
			struct Point next_buy;
			int cnt_type = cnt_com.type;
			int cnt_order = cnt_com.order;
			int i;
			for (i = cnt_order + 1; i <= com[cnt_type].number; i++) {
				if (com[cnt_type].object[i].quality > cnt_com.quality) {
					break;
				}
			}
			int next_order = i;
			if (next_order > com[cnt_type].number) {
				break;
			}
			if (total + com[cnt_type].object[cnt_order].price < com[cnt_type].object[next_order].price) {
				break;
			}
			else {
				buy.pop();
				total = total - com[cnt_type].object[next_order].price + com[cnt_type].object[cnt_order].price;
				next_buy.type = cnt_type;
				next_buy.price = com[cnt_type].object[next_order].price;
				next_buy.quality = com[cnt_type].object[next_order].quality;
				next_buy.order = next_order;
				buy.push(next_buy);
			}
		}
		min_q = buy.top().quality;
		printf("%lld\n", min_q);
	}	
	return 0;
}
