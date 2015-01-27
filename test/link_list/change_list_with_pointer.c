#include <stdio.h>

struct book_list {
    int    price;
    char   name[10];
    struct book_list * next;
};

static struct book_list * book_list_add(struct book_list *head, struct book_list *new_book) {
    struct book_list *p = head;
    while (p)
        p = p->next;
    if (p)
        p->next = new_book;
    else
        head = new_book;

    return head;
}

static struct book_list * book_list_add_2(struct book_list *head, struct book_list *new_book) {
    struct book_list **p = &head;
    while (*p)
        p = &(*p)->next;
    if (*p)
        (*p)->next = new_book;
    else
        *p = new_book;

    return head;
}

static void book_list_dump(struct book_list *head) {
    struct book_list *p = head;
    while (p) {
        printf("book name = %s price = %d\n", p->name, p->price); 
        p = p->next;
    }

}

int main() {
    struct book_list **head = NULL; 
    *head = NULL;
    struct book_list book = {100, "C++", NULL};
    //*head = book_list_add_2(*head, &book);
    *head = book_list_add(*head, &book);
    book_list_dump(*head);
    return 0;
}
