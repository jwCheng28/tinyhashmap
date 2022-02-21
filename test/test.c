#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "hashmap.h"

int main(int argc, char **argv) {
    hashmap *hm = create_hashmap();

    printf("Inserting key: hello, value: world\n");
    insert_item(hm, "hello", "world");

    printf("Getting item from key hello: %s\n", (char*) get_item(hm, "hello"));

    printf("Deleting key hello\n");
    if (delete_item(hm, "hello")==1) printf("Delete success\n");
    else printf("Delete failed\n");

    delete_hashmap(hm);
    return 0;
}
