#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;
const int MAX_NUMBER = 10000;
int integer_number;
int ans[MAX_NUMBER];
int tmp[MAX_NUMBER];
void solve(int left, int right) {
    if(left == right)
        return ;
    memcpy(tmp,ans,sizeof(ans));
    int i, j;
    for(i = left, j = left; i <= right; i += 2, j++) {
        ans[j] = tmp[i];
    }

    for(i = left + 1; i <= right; i += 2, j++) {
        ans[j] = tmp[i];
    }
    solve(left, (left + right) / 2);
    solve((left + right) / 2 + 1,right);
}
int main() {
    freopen("input.txt","r",stdin);
    while(1) {
        
        cin >> integer_number;
        if(integer_number == 0)
            break;
        for(int i = 0; i < integer_number; i++) {
            ans[i] = i;
        }
        
        solve(0, integer_number - 1);
        cout << integer_number << ": ";
        for(int i = 0; i < integer_number; i++) {
            if(i == 0)
                cout << ans[i];
            else
                cout << " " << ans[i];
        }
        cout << endl;
    }
    return 0;
}
