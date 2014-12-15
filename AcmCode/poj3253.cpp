/**
 *FILENAME: poj3253.cpp
 *AUTHOR: XIANG CHANG SHENG
 *CREATE ON: 2012-12-29
 */
#include <iostream>
#include <cstdio>

using namespace std;

const int MAX_LENTH = 20020;
int planks_lenth[MAX_LENTH];
int lenth;

/**
 *DESCRIPTION:
 *To count the minimun sum of n intergers.
 *Just like the huffman,we use minimun heap to
 *implement this
 */
void perlocate_down(int index) {
    int temp, child;
    for (temp = planks_lenth[index]; index * 2 <= lenth; index = child) {
        
        child = index * 2;
        
        if (child + 1 <= lenth && planks_lenth[child] > planks_lenth[child + 1]) {
            child = index * 2 + 1;
        }

        if (temp > planks_lenth[child]) {
            planks_lenth[index] = planks_lenth[child];
        }
        else {
            break;
        }
    }
    planks_lenth[index] = temp;
}

void build_heap() {
    
    for (int i = lenth / 2; i > 0; i--) {
        perlocate_down(i);
        
    }
}
void insert(int key) {
    int i;
    
    for (i = ++lenth; i > 1 && key < planks_lenth[i / 2]; i /= 2) {
        planks_lenth[i] = planks_lenth[i / 2];
    }
    
    planks_lenth[i] = key;
    
}

int delete_min() {
    int last_element = planks_lenth[lenth--];
    int min = planks_lenth[1];
    int index, child;
    for (index = 1; index *2 <= lenth; index = child) {
        child = index * 2;
        if (child + 1 <= lenth && planks_lenth[child] > planks_lenth[child + 1]) {
            child = child + 1;
        }

        if (last_element > planks_lenth[child]) {
            planks_lenth[index] = planks_lenth[child];
        }
        else {
            break;
        }
    }
    planks_lenth[index] = last_element;

    return min;
}

int main() {
    freopen("input.txt","r",stdin);
    cin >> lenth;
    for (int i = 1; i <= lenth; i++) {
        cin >> planks_lenth[i];
    }
    
    build_heap();
    
    long long sums = 0;

    for (int i = lenth; i > 1; i--) {
        int min_1 = delete_min();
        int min_2 = delete_min();
        int one_saw = min_1 + min_2;
        sums += one_saw;
        insert(one_saw);
    }
    
    cout << sums << endl;
    
    return 0;
    
}
