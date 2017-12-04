#ifndef FOREST_NODE_H_
#define FOREST_NODE_H_

#include <stdlib.h>
#include "huff_tree_node.h"

typedef struct forest_node{
  huff_tree_node* val;
  struct forest_node* next;
}forest_node;

forest_node* new_fnode(huff_tree_node* node);

void forest_node_free(forest_node* head);

#endif
