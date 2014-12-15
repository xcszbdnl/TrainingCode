#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX_NUMBER = 20050;
int niceness[MAX_NUMBER];
int main() {
    freopen("input.txt","r",stdin);
    int test_case;
    cin >> test_case;
    int case_number = 1;
    while(test_case--) {
        int bus_stop;
        cin >> bus_stop;
        bus_stop--;
        char input[20];
        cin.get();
        for (int i = 0; i < bus_stop; i++) {
            cin.getline(input,20);
            int j,symbol;
            for (j = 0; input[j] == ' '; j++)
                ;
            if(input[j] == '-') {
                symbol = -1;
                j++;
            }
            else
                symbol = 1;
            int v;
            for (v = 0; input[j]; j++) {
                v = v * 10 + input[j] - '0';
            }
            niceness[i] = v * symbol;
        }
        int begin, end;
        begin = end = 0;
        int ans_begin = begin, ans_end = end;
        int max_niceness, cnt_niceness;
        max_niceness = cnt_niceness = niceness[0];
        for (int i = 1; i < bus_stop; i++) {
            if (cnt_niceness + niceness[i] < niceness[i]) {
                cnt_niceness = niceness[i];
                begin = i;
            }
            else {
                cnt_niceness += niceness[i];
            }
            if (cnt_niceness >=  max_niceness) {
                if (cnt_niceness > max_niceness) {
                    ans_end = i;
                    ans_begin = begin;
                    max_niceness = cnt_niceness;
                }
                else {
                    if (i - begin > ans_end - ans_begin) {
                        ans_begin = begin;
                        ans_end = i;
                        max_niceness = cnt_niceness;
                    }
                }
            }
        }
        if (max_niceness < 0) {
            cout << "Route " << case_number << " has no nice parts" << endl;
        }
        else {
            cout << "The nicest part of route " << case_number << " is between stops " << ans_begin + 1 << " and " << ans_end + 2 << endl;
        }
        case_number++;
    }
    return 0;
}
