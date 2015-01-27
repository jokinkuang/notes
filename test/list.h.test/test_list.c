#include "list.h"
#include <stdio.h>

struct user {
    char *name;           
    struct list_head list_member;
};

static void user_init(struct user *user, char *name) {
    user->name = name;
    INIT_LIST_HEAD(&user->list_member);
}

int main(int argc, char **argv) {
    LIST_HEAD(list);    

    struct user user01;
    user_init(&user01, "Terry");
    list_add_tail(&user01.list_member, &list);  

    struct user user02;
    user_init(&user02, "Tom");
    list_add_tail(&user02.list_member, &list);  

    struct user *userp;
    list_for_each_entry(userp, &list, list_member) {
        printf("User: %s\n", userp->name);
    }

    // clear the list;
    // for they are all stack objects, so no need to free 
    INIT_LIST_HEAD(&list);
    return 0;
}

