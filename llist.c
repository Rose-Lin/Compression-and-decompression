#include <stdlib.h>
#include <stdio.h>
#include "llist.h"
#include "llist_node.h"

llist* new_llist(){
  llist* l = malloc(sizeof(llist));
  l->head = NULL;
  l->tail = NULL;
  l->size = 0;
  return l;
}

int llist_size(llist l){
  return l.size;
}

llist* llist_pop(llist* l) {
  if(!l->head) {
    return l;
  } else if (l->size == 1) {
    printf("hh\n");
    llist_node* temp = l->head;
    l->head = NULL;
    l->tail = NULL;
    free(temp);
    l->size = 0;
  } else {
    llist_node* temp = l->head;
    for (int i = 1; i < l->size; i++) {
      temp = temp->next;
    }
    llist_node* n = temp->next;
    l->tail = temp;
    l->size --;
    //free(n);
    temp->next = NULL;
  }
}

llist* llist_add(llist* l, int n){
  if(l->head){
    llist_node_insert_after(l->tail, n);
    l->tail = l->tail->next;
  }else{
    l->head = new_llist_node(n, NULL);
    l->tail = l->head;
  }
  l->size++;
  return l;
}

llist* llist_addFront (llist* l, int n) {
  llist_node* temp = l->head;
  llist_node* node = new_llist_node(n, l->head);
  l->head = node;
  if(!temp) {
    l->tail = l->head;
  }
  l->size ++;
  return l;
}

llist* llist_append(llist* l1, const llist* l2) {
  llist_node* temp = l2->head;
  for(int i = 0; i < l2->size; i ++) {
    l1 = llist_add(l1, temp->data);
    temp = temp->next;
  }
  return l1;
}
