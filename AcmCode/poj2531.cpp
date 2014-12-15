#include<iostream>
#include<cstring>
using namespace std;
const int Max=21
int computer_node[Max][Max];
int choose_node[Max],choose_num;
int un_choose_node[Max],un_choose_num;
int max_traffic;
int nodes;
void dfs(int cur){
	int i,j,temp_max_traffic;
	if(cur==nodes-1){
		for(i=0,temp_max_traffic=0;i<choose_num;i++){
			for(j=0;j<un_choose_num;j++){
				temp_max_traffic += computer_node[choose_node[i]][un_choose_node[j]];
				if(temp_max_traffic>max_traffix)
					max_traffic=temp_max_traffic;
			}
		}
	}
	else{
		choose_node[choose_num++]=cur;
		dfs(cur+1);
		choose_num--;
		un_choose_node[un_choose_num++]=cur;
		dfs(cur+1);
		un_choose_num--;
	}
}



}
int main()
{
	int i,j;
	cin >> nodes;
	for(i=0;i<nodes;i++){
		for(j=0;j<nodes;j++){
			cin >> cpmputer_node[i][j];
		}
	}
	max_traffic=0;
	choose_num=0;
	un_choose_num=0;
	dfs(0);
	cout << max_traffic << endl;
	return 0;
}
