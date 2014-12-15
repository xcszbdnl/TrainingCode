#include <iostream>
#include <cstring>
//#include <stdio.h>
using namespace std;
const int MAX_NUMBER = 101;
const int MAX_STATE = 65000;
const int OFF_SET =32001;
int numbers[MAX_NUMBER];
int vis[MAX_NUMBER][MAX_STATE];
int has_found;
char temp_symbols[MAX_NUMBER];
char ans_symbols[MAX_NUMBER];
int k_number;
int target_number;
int result;
void dfs(int cur) {
    if(cur >= k_number) {
        if (result == target_number) {
            has_found = 1;
            memcpy(ans_symbols,temp_symbols,sizeof(ans_symbols));
        }
        return ;
    }
    if (has_found)
        return ;
    else {
        if (!has_found && (result + numbers[cur]) <= 32000 && (result + numbers[cur]) >= -32000 && !vis[cur][result + numbers[cur] + OFF_SET]) {
            temp_symbols[cur - 1] = '+';
            result += numbers[cur];
            vis[cur][result + OFF_SET] = 1;
            dfs(cur + 1);
            result -= numbers[cur];
        }
        if (!has_found && (result - numbers[cur]) <= 32000 && (result - numbers[cur]) >= -32000 && !vis[cur][result - numbers[cur] + OFF_SET]) {
            temp_symbols[cur - 1] = '-';
            result -= numbers[cur];
            vis[cur][result + OFF_SET] = 1;
            dfs(cur + 1);
            result += numbers[cur];
        }
        if (!has_found && (result * numbers[cur]) <= 32000 && (result * numbers[cur]) >= -32000 && !vis[cur][result * numbers[cur]] + OFF_SET) {
            temp_symbols[cur - 1] = '*';
            result *= numbers[cur];
            vis[cur][result + OFF_SET] = 1;
            dfs(cur + 1);
            result /= numbers[cur];
        }
        if (!has_found && (result % numbers[cur]) == 0 && !vis[cur][result / numbers[cur] + OFF_SET]) {
            temp_symbols[cur - 1] = '/';
            result /= numbers[cur];
            vis[cur][result + OFF_SET] = 1;
            dfs(cur + 1);
            result *= numbers[cur];
        }
    }
}
int main() {
    //freopen("input.txt","r",stdin);
    int test_case;
    cin >> test_case;
    while (test_case--) {
        cin >> k_number;
        has_found = 0;
        memset(vis,0,sizeof(vis));
        for (int i = 0;i < k_number; i++) {
            cin >> numbers[i];
        }
        cin >> target_number;
        result = numbers[0];
        vis[0][result+OFF_SET] = 1;
        dfs(1);
        if (!has_found) {
            cout << "NO EXPRESSION" << endl;
        } else {
            for (int i = 0; i < k_number; i++) {
                cout << numbers[i];
                if (i != k_number - 1)
                cout << ans_symbols[i];
            }
            cout << "=" << target_number;
            cout << endl;
        }
    }
    return 0;
}
