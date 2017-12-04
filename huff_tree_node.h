#ifndef HUFF_TREE_NODE_H_
#define HUFF_TREE_NODE_H_
#include <stdbool.h>

typedef struct huff_tree_node{
  int ch;
  int freq;

  struct huff_tree_node* left;
  struct huff_tree_node* right;
}huff_tree_node;

huff_tree_node* new_node(int c, int freq);

// compare two node. if node1 is smaller than node2, return true
// otherwise return false
bool compare_node(huff_tree_node* node1, huff_tree_node* node2);

// free current node only
void free_node(huff_tree_node* node);


void free_huff_tree(huff_tree_node* huff);

#endif
