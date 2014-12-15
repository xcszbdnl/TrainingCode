#include <iostream>
#include <algorithm>
#include <stdio.h>

using namespace std;
const int MAX_NUMBER = 50005;
const int MAX_LENTH = 2000000000;

int rock_coordinate[MAX_NUMBER];
int rock_number, lenth, remove_number;


int main() {

    while (scanf("%d%d%d", &lenth, &rock_number, &remove_number) != EOF) {
        int low, high;
        high = lenth;
        low = 0;
        for (int i = 1; i <= rock_number; i++) {
            scanf("%d", &rock_coordinate[i]);
        }
        rock_coordinate[0] = 0;
        rock_coordinate[rock_number + 1] = lenth;
        sort(rock_coordinate, rock_coordinate + rock_number + 2);
        while (low <= high) {
            int mid = (low + high) / 2;
            int sum = 0;
            int del_number = 0;
            for (int i = 1; i < rock_number + 2; i++) {
                if (sum + rock_coordinate[i] - rock_coordinate[i - 1] <= mid) {
                    del_number++;
                    sum += rock_coordinate[i] - rock_coordinate[i - 1];                    
                }
                else {
                    sum = 0;
                }
            }
            if (del_number > remove_number ) {
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        printf("%d\n", low);
    }
}
