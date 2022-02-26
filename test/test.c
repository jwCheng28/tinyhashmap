#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "hashmap.h"

#define STRSIZE 16

void gen_rand_string(char str[], int length) {
    for (int i = 0; i < length-1; ++i) {
        str[i] = rand() % 26 + 'a';
    }
    str[length-1] = 0;
}

void print_key_val_array(char key_array[][STRSIZE], char val_array[][STRSIZE], int arr_len) {
    for (int i = 0; i < arr_len; ++i) {
        printf("Key: %s, Value: %s\n", key_array[i], val_array[i]);
    }
}

void hm_insert_test_key_val(hashmap *hm, char key_array[][STRSIZE], char val_array[][STRSIZE], int arr_len) {
    for (int i = 0; i < arr_len; ++i) {
        insert_item(hm, key_array[i], val_array[i]);
    }
}

void hm_check_key_val(hashmap *hm, char key_array[][STRSIZE], char val_array[][STRSIZE], int arr_len) {
    int correct = 0;
    for (int i = 0; i < arr_len; ++i) {
        printf("Getting value (key: %s) ->\t", key_array[i]);
        char *stored_val = get_item(hm, key_array[i]);
        if (!stored_val) {
            printf("Get failed %s\n", key_array[i]);
            continue;
        }
        if (!strcmp(val_array[i], stored_val)) {
            correct++;
            printf("Get success (value: %s)\n", stored_val);
        }
    }
    printf("%d/%d matching key values\n", correct, arr_len);
}

int main(int argc, char **argv) {
    srand(time(NULL));
    hashmap *hm = create_hashmap();

    int arr_size = 64;

    char key_array[arr_size][STRSIZE];
    char val_array[arr_size][STRSIZE];
    for (int i = 0; i < arr_size; ++i) {
        gen_rand_string(key_array[i], STRSIZE);
        gen_rand_string(val_array[i], STRSIZE);
    }
    hm_insert_test_key_val(hm, key_array, val_array, arr_size);
    hm_check_key_val(hm, key_array, val_array, arr_size);

    delete_hashmap(hm);
    return 0;
}
