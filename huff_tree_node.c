#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "huff_tree_node.h"


huff_tree_node* new_node(int c, int freq){
  huff_tree_node* new = malloc(sizeof(huff_tree_node));
  new->ch = c;
  new->freq = freq;
  new->left = NULL;
  new->right = NULL;
  return new;
}
//Is node1 smaller than node2 ?
bool compare_node(huff_tree_node* node1, huff_tree_node* node2){
  if(node1->freq == node2->freq){
    if(node1->ch < node2->ch){
      return true;
    } else {
      return false;
    }
  } else if (node1->freq <node2->freq){
    return true;
  } else {
    return false;
  }
}

void free_node(huff_tree_node* node){
  free(node);
}

void free_huff_tree(huff_tree_node* head){
  if(head->left) {
    free_huff_tree(head->left);
  }
  if(head->right) {
    free_huff_tree(head->right);
  }
  free(head);
}
