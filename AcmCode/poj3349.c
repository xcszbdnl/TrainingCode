/**
 *FILENAME： poj3349.c
 *AUTHOR: XIANG CHANG SHENG
 *CREATE ON:2012-1-31
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 999983
#define MAX_NUMBER 100005

/**
 *DESCRIPTION:
 Using hash to solve the problem.
 Hash the sum of all arms.If the hash key is the same,we check whether the snows are the same.
 Using the dynamic alloc.
 */
struct HashNode {
    int arm_lenth[6];
    struct HashNode *next;
};
struct HashNode *hash_table[HASHSIZE];
struct HashNode leafs[MAX_NUMBER];

int hashKey(struct HashNode hash_node) {
    int i, sums;
    for (i = 0, sums = 0; i < 6; i++) {
        sums += hash_node.arm_lenth[i];
    }
    return sums % HASHSIZE;
}

int check(int key) {
    int hash = hashKey(leafs[key]);
    int i, j, same_number, start_point;
    struct HashNode *hash_node;
    for (hash_node = hash_table[hash]; hash_node != NULL; hash_node = hash_node->next) {
        for (start_point = 0; start_point < 6; start_point++) {
            if (hash_node->arm_lenth[start_point] != leafs[key].arm_lenth[0]) {
                continue;
            }
            i = start_point;
            same_number = 0;
            for (j = 0; j < 6; j++) {
                if (leafs[key].arm_lenth[j] != hash_node->arm_lenth[i]) {
                    break;
                }
                same_number++;
                i++;
                i = i % 6;
            }
            if (same_number == 6) {
                return 1;
            }
            i = start_point;
            same_number = 0;
            for (j = 0; j < 6; j++) {
                if (leafs[key].arm_lenth[j] != hash_node->arm_lenth[i]) {
                    break;
                }
                same_number++;
                i--;
                if (i < 0) {
                    i += 6;
                }
            }
            if (same_number == 6) {
                return 1;
            }
        }
    }
    return 0;
}

void insert(int key) {
    struct HashNode *hash_node;
    int i;
    int hash = hashKey(leafs[key]);
    hash_node = (struct HashNode *)malloc(sizeof(struct HashNode));
    for (i = 0; i < 6; i++) {
        hash_node->arm_lenth[i] = leafs[key].arm_lenth[i];
    }
    if (hash_table[hash] == NULL) {
        hash_node->next = NULL;
        hash_table[hash] = hash_node;
    }
    else {
        hash_node->next = hash_table[hash]->next;
        hash_table[hash]->next = hash_node;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int numbers, i, j, flag;
    scanf("%d",&numbers);
    
    for (i = 0; i < numbers; i++) {
        for (j = 0; j < 6; j++) {
            scanf("%d", &leafs[i].arm_lenth[j]);
        }
        flag = check(i);
        if (flag) {
            break;
        }
        insert(i);
    }
    
    if (flag) {
        printf("Twin snowflakes found.\n");
    }
    
    else {
        printf("No two snowflakes are alike.\n");
    }
    
    return 0;
}
