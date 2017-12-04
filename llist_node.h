#ifndef LLIST_NODE_H_
#define LLIST_NODE_H_

typedef struct llist_node{
  int data;
  struct llist_node* next;
}llist_node;

llist_node* new_llist_node(int n, llist_node* next);

void llist_node_insert_after(llist_node* node, int n);

void llist_node_free(llist_node* head);

#endif
