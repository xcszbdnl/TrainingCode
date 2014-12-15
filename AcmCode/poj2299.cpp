/**
 *FILENAME: poj2299.cpp
 *AUTHOR: XIANG CHANG SHENG
 *CREATE ON: 2012-12-30
 */
#include <iostream>
#include <cstdio>

using namespace std;
const int MAX_NUMBER = 500010;

int sort_array[MAX_NUMBER];
int temp_array[MAX_NUMBER];
int lenth;
long long count;
/**
 *DESCRIPTION:
 *To count the reverse pair in an array
 *We use merge sort to count this.
 */
void merge_count(int *array_to_count, int *temp, int lower, int upper) {
    if (upper - lower > 1) {
        int mid = lower + (upper - lower) / 2;
        int y = mid, x = lower, i = lower;
        merge_count(array_to_count, temp, lower, mid);
        merge_count(array_to_count, temp, mid, upper);
        while (x < mid || y < upper) {
            if (y >= upper || (x < mid && array_to_count[x] <= array_to_count[y])) {
                temp[i++] = array_to_count[x++];
            }
            else {
                temp[i++] = array_to_count[y++];
                count += mid - x;
            }
        }
        for (int i = lower; i < upper; i++) {
            array_to_count[i] = temp[i];
        }
    }
}

int main() {
    
    freopen("input.txt","r",stdin);
    while (cin >> lenth) {

        if (lenth == 0) {
            break;
        }
        for (int i = 0; i < lenth; i++) {
            cin >> sort_array[i];
        }
        count = 0;
        
        merge_count(sort_array, temp_array, 0, lenth);
        
        cout << count << endl;
    }
    return 0;
}
