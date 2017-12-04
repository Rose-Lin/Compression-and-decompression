#ifndef LLIST_H_
#define LLIST_H_

#include "llist_node.h"
typedef struct llist{
  llist_node* head;
  llist_node* tail;
  int size;
}llist;

llist* new_llist();

int llist_size(llist l);

llist* llist_add(llist* l, int n);

llist* llist_pop(llist* l);

llist* llist_addFront(llist* l, int n);

llist* llist_append(llist* l1, const llist* l2);


#endif
