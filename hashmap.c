#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashmap.h"

#ifdef DEBUG
#define BREAK \
        printf("Debug Info: \tFile: %s\tFunction: %s\tLine: %d\n\n", __FILE__, __func__, __LINE__)
#else
#define BREAK //
#endif

#define INIT_SIZE 32

typedef struct {
    char *key;
    void *val;
} hashmap_obj;

struct hashmap {
    unsigned int max_size;
    unsigned int item_count;
    hashmap_obj **obj_array;
};

static hashmap_obj DELETED;

hashmap_obj* create_obj(char *key, void *val) {
    hashmap_obj *obj = malloc(sizeof(hashmap_obj));
    obj->key = malloc(strlen(key));
    strncpy(obj->key, key, strlen(key));
    obj->val = val;
    return obj;
}

void delete_obj(hashmap_obj *obj) {
    free(obj->key);
    free(obj);
}

hashmap* create_hashmap() {
    hashmap *hm = malloc(sizeof(hashmap));
    hm->max_size = INIT_SIZE;
    hm->item_count = 0;
    hm->obj_array = malloc(hm->max_size * sizeof(hashmap_obj*));
    memset(hm->obj_array, 0, hm->max_size * sizeof(hashmap_obj*));
    return hm;
}

void delete_hashmap(hashmap *hm) {
    for (int i = 0; i < hm->max_size; ++i) {
        if (hm->obj_array[i] && hm->obj_array[i] != &DELETED) {
            delete_obj(hm->obj_array[i]);
        }
    }
    free(hm->obj_array);
    free(hm);
}

unsigned int hash(const char *string, const unsigned int c) {
    unsigned int len = strlen(string);
    unsigned int res = 0;
    for (int i = 0; i < len; ++i) {
        res += (string[i]<<3) + (string[i]<<5) + (string[i]<<7);
        res ^= 1719435967;
        res *= 11 * (c+1);
    }
    return res;
}

void insert_item(hashmap *hm, char *key, void *val) {
    hashmap_obj *obj = create_obj(key, val);
    unsigned int index = hash(obj->key, 0) % hm->max_size;
    unsigned int retries = hm->max_size >> 1;
    unsigned int trial = 1;
    while (hm->obj_array[index] && hm->obj_array[index] != &DELETED && trial < retries) {
        index = hash(obj->key, trial) % hm->max_size;
        trial++;
    }
    if (trial >= retries) {
        // TODO: increase size of map
    }
    hm->obj_array[index] = obj;
    hm->item_count++;
}

void* get_item(hashmap *hm, char *key) {
    unsigned int index = hash(key, 0) % hm->max_size;
    unsigned int retries = hm->max_size >> 1;
    unsigned int trial = 1;
    while (hm->obj_array[index] && trial < retries) {
        if (hm->obj_array[index] != &DELETED && !strcmp(hm->obj_array[index]->key, key)) {
            return hm->obj_array[index]->val;
        }
        index = hash(key, trial) % hm->max_size;
        trial++;
    }
    return NULL;
}

int delete_item(hashmap *hm, char *key) {
    unsigned int index = hash(key, 0) % hm->max_size;
    unsigned int retries = hm->max_size >> 1;
    unsigned int trial = 1;
    while (hm->obj_array[index] && trial < retries) {
        if (!strcmp(hm->obj_array[index]->key, key)) {
            delete_obj(hm->obj_array[index]);
            hm->obj_array[index] = &DELETED;
            return 1;
        }
        index = hash(key, trial) % hm->max_size;
        trial++;
    }
    return -1;
}
