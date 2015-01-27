/*
 * File: dlist.h
 * Author: Terry Lei <freedom@ema-tech.com>
 * Brief: A simple double-link list.
 */
#ifndef _DLIST_H_
#define _DLIST_H_

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

struct dlist {
    void *data;
    struct dlist *next;
    struct dlist *prev;
};

struct dlist * dlist_new();
void dlist_release(struct dlist *);

unsigned int dlist_length(struct dlist *);

void dlist_push_back(struct dlist *, void *elem);
void dlist_push_front(struct dlist *, void *elem);
void * dlist_pop_back(struct dlist *);
void * dlist_pop_front(struct dlist *);

/* remove the node from list;
 * after remove, node is not accessable any more!!!
 * it returns the next valid node.
 */
struct dlist* dlist_remove(struct dlist *node);

static inline bool dlist_empty(struct dlist *list) {
    return list->next == list;
}

#define dlist_read(node)    ((node)->data)

/* These methods are for *iterate* :
 *
 * struct dlist *node;
 * for (node=dlist_head(list); node!=dlist_end(list); node=dlist_next(node)) {
 *     // do something
 * }
 */
static inline struct dlist * dlist_head(struct dlist *list) {
    assert(list->data == NULL);
    return list->next;
}

static inline struct dlist * dlist_end(struct dlist *list) {
    assert(list->data == NULL);
    return list;
}

static inline struct dlist * dlist_next(struct dlist *node) {
    return node->next;
}

#ifdef __cplusplus
}
#endif

#endif
