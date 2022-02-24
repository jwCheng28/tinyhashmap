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

hashmap* new_hashmap(const unsigned int new_size) {
    hashmap *hm = malloc(sizeof(hashmap));
    hm->max_size = new_size;
    hm->item_count = 0;
    hm->obj_array = malloc(hm->max_size * sizeof(hashmap_obj*));
    memset(hm->obj_array, 0, hm->max_size * sizeof(hashmap_obj*));
    return hm;
}

hashmap* create_hashmap() {
    return new_hashmap(INIT_SIZE);
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

void hm_resize(hashmap *hm, const unsigned int new_size) {
    hashmap *new_hm = new_hashmap(new_size);
    for (int i = 0; i < hm->max_size; ++i) {
        if (hm->obj_array[i] && hm->obj_array[i] != &DELETED) {
            insert_item(new_hm, hm->obj_array[i]->key, hm->obj_array[i]->val);
        }
    }
    hashmap_obj **old_items = hm->obj_array;
    hm->obj_array = new_hm->obj_array;
    new_hm->obj_array = old_items;

    new_hm->max_size = hm->max_size;
    hm->max_size = new_size;

    hm->item_count = new_hm->item_count;
    delete_hashmap(new_hm);
}

void hm_size_inc(hashmap *hm) {
    unsigned int new_size = hm->max_size<<1;
    hm_resize(hm, new_size);
}

void hm_size_dec(hashmap *hm) {
    unsigned int new_size = hm->max_size>>1;
    hm_resize(hm, new_size);
}

void hm_check_resize(hashmap *hm) {
    unsigned int quarter_max_size = hm->max_size>>2;
    if (hm->max_size > INIT_SIZE) {
        if (hm->item_count >= 3*quarter_max_size) {
            hm_size_inc(hm);
        } else if (hm->item_count <= quarter_max_size) {
            hm_size_dec(hm);
        }
    }
}

unsigned int hash(const char *string, const unsigned int c) {
    unsigned int len = strlen(string);
    unsigned int res = 0;
    for (int i = 0; i < len; ++i) {
        res += (string[i]<<3) + (string[i]<<5) + (string[i]<<7);
        res ^= 1719435967;
        res *= 11;
    }
    return res + c;
}

void insert_item(hashmap *hm, char *key, void *val) {
    hm_check_resize(hm);
    hashmap_obj *obj = create_obj(key, val);
    unsigned int index = hash(obj->key, 0) % hm->max_size;
    unsigned int constant = 0;
    while (hm->obj_array[index] && hm->obj_array[index] != &DELETED && constant < hm->max_size) {
        constant++;
        index = hash(obj->key, constant) % hm->max_size;
    }
    hm->obj_array[index] = obj;
    hm->item_count++;
}

void* get_item(hashmap *hm, char *key) {
    hm_check_resize(hm);
    unsigned int index = hash(key, 0) % hm->max_size;
    unsigned int constant = 0;
    while (hm->obj_array[index] && constant < hm->max_size) {
        if (hm->obj_array[index] != &DELETED && !strcmp(hm->obj_array[index]->key, key)) {
            return hm->obj_array[index]->val;
        }
        constant++;
        index = hash(key, constant) % hm->max_size;
    }
    return NULL;
}

int delete_item(hashmap *hm, char *key) {
    hm_check_resize(hm);
    unsigned int index = hash(key, 0) % hm->max_size;
    unsigned int constant = 0;
    while (hm->obj_array[index] && constant < hm->max_size) {
        if (!strcmp(hm->obj_array[index]->key, key)) {
            delete_obj(hm->obj_array[index]);
            hm->obj_array[index] = &DELETED;
            return 1;
        }
        constant++;
        index = hash(key, constant) % hm->max_size;
    }
    return -1;
}
