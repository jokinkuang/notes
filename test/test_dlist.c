#include "dlist.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main(int argc, char **argv) {
    struct dlist *list = dlist_new();
    assert(dlist_length(list) == 0);
    dlist_push_back(list, "str01"); 
    dlist_push_back(list, "str02");
    dlist_push_front(list, "str03");
    assert(dlist_length(list) == 3);

    struct dlist *node;
    for (node=dlist_head(list); node!=dlist_end(list); node=dlist_next(node))
        printf("%s\n", (char *)dlist_read(node));

    node = dlist_head(list); 
    while (node != dlist_end(list)) {
        if (strcmp("str02", (char *)dlist_read(node)) == 0)
            node = dlist_remove(node);
        else 
            node = dlist_next(node);
    }
    assert(dlist_length(list) == 2);

    printf("after remove:\n");
    for (node=dlist_head(list); node!=dlist_end(list); node=dlist_next(node))
        printf("%s\n", (char *)dlist_read(node));

    assert(strcmp("str03", (char *)dlist_pop_front(list)) == 0);
    assert(strcmp("str01", (char *)dlist_pop_front(list)) == 0);
    assert(dlist_length(list) == 0);

    dlist_release(list);
    return 0;
}
