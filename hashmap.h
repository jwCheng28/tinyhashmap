#ifndef __HASHMAP_H__
#define __HASHMAP_H__

typedef struct hashmap hashmap;

// Constructor & Destructor
hashmap* create_hashmap();
void delete_hashmap(hashmap *hm);

int insert_item(hashmap *hm, char *key, void *val);
void* get_item(hashmap *hm, char *key);
int delete_item(hashmap *hm, char *key);

#endif // __HASHMAP_H__
