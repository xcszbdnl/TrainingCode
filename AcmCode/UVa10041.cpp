#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX_NUMBER = 550;
int street_number[MAX_NUMBER];
int main() {
    freopen("input.txt","r",stdin);
    int test_case;
    cin >> test_case;
    while(test_case--) {
        int relatives_number;
        cin >> relatives_number;
        for (int i = 0; i < relatives_number; i++) {
            cin >> street_number[i];
        }
        sort(street_number,street_number + relatives_number);
        int distance = 0;
        int number = street_number[relatives_number / 2];
        for (int i = 0; i < relatives_number; i++) {
            if (i < relatives_number / 2) {
                distance += number - street_number[i];
            }
            else {
                distance += street_number[i] - number;
            }
        }
        cout << distance << endl;
    }
    return 0;
}
                    
            
