#include <iostream>
#include <cstring>
#include <algorithm>
#include <string.h>
#include <stdio.h>
using namespace std;
const int MAX_NUMBER = 101;
struct Agencys {
    int dollars_a;
    int dollars_b;
    int cost;
    char name[20];
}agencys[MAX_NUMBER];
int start_workload;
int target_workload;
int agency_number;
bool cmp(Agencys a,Agencys b) {
    if (a.cost < b.cost) {
        return true;
    }
    else if(a.cost == b.cost && strcmp(a.name,b.name) < 0) return true;
    else
        return false;
}
                
                
void solve() {
    for(int i = 0; i< agency_number; i++) {
        int cnt_workload = start_workload;
        while(cnt_workload > target_workload) {
            int half_money;
            int cut_money;
            int half = (cnt_workload + 1) / 2;
            half_money = agencys[i].dollars_b;
            cut_money = (cnt_workload - half) * agencys[i].dollars_a;
            if(half >= target_workload && cut_money > half_money) {
                agencys[i].cost += half_money;
                cnt_workload -= half;
            } else {
                agencys[i].cost += (cnt_workload - target_workload) * agencys[i].dollars_a;
                cnt_workload = target_workload;
            }
        }
    }
    sort(agencys,agencys + agency_number,cmp);
    for(int i = 0; i < agency_number; i++) {
        cout << agencys[i].name << " " << agencys[i].cost << endl;
    }
}
int main() {
    freopen("input.txt","r",stdin);
    int test_case;
    cin >> test_case;
    int case_number = 1;    
    while(test_case--) {
        cin >> start_workload >> target_workload >> agency_number;
        for(int i = 0; i < agency_number; i++) {
            char temp[50];
            cin >> temp;
            int j;
            for(j = 0; temp[j] >='A' && temp[j] <='Z'; j++) {
                agencys[i].name[j] = temp[j];
            }
            j++;
            for(int v = 0; temp[j] != ','; j++) {
                v = v * 10 + temp[j] - '0';
                agencys[i].dollars_a = v;
            }
            j++;
            for(int v = 0; temp[j]; j++) {
                v = v * 10 + temp[j] - '0';
                agencys[i].dollars_b = v;
            }
            agencys[i].cost = 0;
        }
        cout << "Case " << case_number << endl;
        solve();
        case_number++;
    }
    return 0;
}
            
                
            
            
                
        
