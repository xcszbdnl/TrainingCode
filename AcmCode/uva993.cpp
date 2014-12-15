#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;
int prime[] = {2,3,4,5,6,7,8,9};
int prime_number[8];
long long target_number;
int main(){
    freopen("input.txt","r",stdin);
    int test_case;
    cin >> test_case;
    while(test_case--) {
        int target_number;
        cin >> target_number;
        memset(prime_number,0,sizeof(prime_number));
        if(target_number == 0 || target_number == 1)
            cout << target_number << endl;
        else {
            for(int i = 7; i >= 0; i--) {
                if(target_number % prime[i] == 0) {
                    prime_number[i]++;
                    target_number /= prime[i];
                }
            }
            if(target_number != 1) {
                cout << -1 << endl;
            }
            else {
                for(int i = 0; i < 8; i++) {
                    if(prime_number[i]){
                        for(int j = 0; j < prime_number[i]; j++){
                            cout << prime[i];
                        }
                    }
                }
                cout << endl;
            }
        }
    }
    return 0;
}
         
