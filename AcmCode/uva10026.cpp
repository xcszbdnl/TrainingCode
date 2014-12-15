#include <iostream>
#include <algorithm>
using namespace std;
const int MAX_ORDER = 1001;
struct node {
	int time;
	int fine;
	double value;
	int number;
};
node all_order[MAX_ORDER];
bool cmp(node x,node y) {
	if(x.value > y.value)
		return true;
	else
		return false;
}
int main()
{
	freopen("./input.txt","r","stdin");
	int test_case;
	cin >> test_case;
	cin.get();
	cin.get();
	while (test_case--) {
		int orders;
		cin >> orders;
		for (int i = 0; i < orders; i++) {
			cin >> all_order[i].time;
			cin >> all_order[i].fine;
			all_order[i].number = i;
		}
		for (int i = 0; i < orders; i++) {
			all_order.value[i] = all_order.time[i] / all_order.fine[i];
		}
		sort(all_order,all_order+orders,cmp);
		for (int i = 0; i < orders-1; i++) {
			cout << " " << all_order[i].number+1;
		}
		cout << all_order[orders-1].number+1;
	}
	return 0;
}
		
