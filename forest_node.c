#include <stdlib.h>
#include "forest_node.h"

forest_node* new_fnode(huff_tree_node* node) {
  forest_node* new = malloc(sizeof(forest_node));
  new->val = node;
  new->next = NULL;
  return new;
}

void forest_node_free(forest_node* head) {
  forest_node* cur = head;
  while(cur) {
    head = cur;
    cur = cur->next;
    free(head);
  }
}
