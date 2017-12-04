#include<stdlib.h>
#include "llist_node.h"

llist_node* new_llist_node(int n, llist_node* next){
  llist_node* new = malloc(sizeof(llist_node));
  new->data = n;
  new->next = next;
  return new;
}

void llist_node_insert_after(llist_node* node, int n){
  node->next = new_llist_node(n, NULL);
}

void llist_node_free(llist_node* head){
  llist_node* cur = head;
  while(cur){
    head = cur;
    cur =  cur->next;
    free(head);
  }
}
