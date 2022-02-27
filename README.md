# tinyhashmap
Hashmaps are a pretty convenient data structure, however as far as I know there isn't a standard library for any data structures in C.
Hence, the goal of tinyhashmap is to create a simply hashmap that may come in handy for future personal usage.

## How To Use
The API for this hashmap is fairly simple; currently there's only 5 type of functions for this hashmap: constructor, destructor, insert, get, and delete.

Here's an example of the hashmap in action.
```c
#include <stdio.h>

#include "hashmap.h"

int main(int argc, char **argv) {
    hashmap *hm = create_hashmap();

    char *key = "Hello", *value = "World";
    
    printf("Inserting key (%s), value (%s)\n\n", key, value);
    insert_item(hm, key, value);
    
    printf("Getting value with key (%s)\n", key);
    printf("Received value: %s\n\n", (char*) get_item(hm, key));
    
    printf("Deleting key (%s)\n", key);
    if (delete_item(hm, key)==1) {
        printf("Delete Success\n");
    } else {
        printf("Delete Failed\n");
    }

    delete_hashmap(hm);
    return 0;
}
```


## Current Progress

### Completed
 - hashmap creation and destructor (no memory leaks)
 - hashing function
 - insert, get, and delete 
 - resize function
 - full testing code

