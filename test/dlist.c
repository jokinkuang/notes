/*
 * File: dlist.c
 * Author: Terry Lei <freedom@ema-tech.com>
 * Brief: Implemtation of types defined in dlist.h
 */
#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct dlist * dlist_new() {
    struct dlist *list = malloc(sizeof(*list));    
    list->data = NULL;
    list->next = list->prev = list;
    return list;
}

void dlist_release(struct dlist *list) {
    assert(list->data == NULL);
    struct dlist *next;    
    struct dlist *cur = list->next;
    for (cur=list->next; cur!=list; cur=next) {
        next = cur->next;     
        free(cur);
    }
    free(list);
}

unsigned int dlist_length(struct dlist *list) {
    assert(list->data == NULL);
    unsigned int len = 0;
    struct dlist *p = list->next;    
    while (p != list) {
        len++;
        p = p->next;
    }
    return len;
}

void dlist_push_back(struct dlist *list, void *elem) {
    assert(list->data == NULL);
    struct dlist *node = malloc(sizeof(*node));
    node->data = elem;
    node->next = list;
    node->prev = list->prev;
    list->prev->next = node;
    list->prev = node;
}    

void dlist_push_front(struct dlist *list, void *elem) {
    assert(list->data == NULL);
    struct dlist *node = malloc(sizeof(*node));
    node->data = elem;
    node->next = list->next;
    node->prev = list; 
    list->next->prev = node;
    list->next = node;
}

struct dlist* dlist_remove(struct dlist *node) {
    assert(node->data != NULL && "Program error: it is not a node!");
    node->prev->next = node->next;
    node->next->prev = node->prev;
    struct dlist *next = node->next;
    free(node);
    return next;
}

void * dlist_pop_back(struct dlist *list) {
    assert(list->data == NULL);
    if (dlist_empty(list))
        return NULL;
    struct dlist *node = list->prev;
    void *elem = node->data;
    (void)dlist_remove(node);
    return elem;
}

void * dlist_pop_front(struct dlist *list) {
    assert(list->data == NULL);
    if (dlist_empty(list))
        return NULL;
    struct dlist *node = list->next;
    void *elem = node->data;
    (void)dlist_remove(node);
    return elem;
}

