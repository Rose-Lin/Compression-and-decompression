#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "forest.h"
#include "forest_node.h"
#include "huff_tree_node.h"
#include "llist_node.h"
#include "llist.h"
// get the frequency for each char in the input file
int* make_freq_table(char* filename){
  FILE* file = fopen(filename,"r");
  if(!file){
    printf("Cannot open file.\n");
    return NULL;
  }
  int* freq_table = malloc(sizeof(int) * 256);
  for (int i = 0; i < 256; i ++) {
    freq_table[i] = 0;
  }
  while(!feof(file)) {
    int c = fgetc(file);
    if(c > 0) {
      freq_table[c]++;
    }
  }
  return freq_table;
}

// get the maximum frequency in the frequency table
int getMaxFreq (int* freqtable) {
  int max = 0;
  for (int i = 0; i < 256; i ++) {
    if (freqtable[i] > max) {
      max = freqtable[i];
    }
  }
  return max;
}

// make the forest
forest* makeForest(forest* f, int* ftable) {
  int freq = 1;
  int max = getMaxFreq(ftable);
  while(freq < max + 1) {
    for (int i = 0; i < 256; i ++){
      if (ftable[i] == freq) {
        huff_tree_node* hnew = new_node(i, freq);
        forest_node* fnew = new_fnode(hnew);
        insert_after(f, fnew);
      }
    }
    freq ++;
  }
  return f;
}

huff_tree_node* makeTree(forest* f) {
  huff_tree_node* head = NULL;
  int count = -1;
  while(f->size > 1) {
    int f1 = f->head->val->freq;
    int f2 = f->head->next->val->freq;
    head = new_node(count, f1 + f2);
    head->left = f->head->val;
    head->right = f->head->next->val;
    count --;
    forest_node* result = new_fnode(head);
    f = ordInsert(f, result);
    pop(f);
    pop(f);
  }
  return head;
}

llist* get_code(llist* l, huff_tree_node* root, int c){
  if(root) {
    if(root->ch < 0) {
      if(root->left->ch == c) {
        l = llist_add(l, 0);
        return l;
      } else if (root->right->ch == c) {
        l = llist_add(l, 1);
        return l;
      } else if(root->left->ch < 0){
        llist* temp = new_llist();
        temp = get_code(temp, root->left, c);
        if(!temp->head) {
          l = get_code(llist_add(l, 1), root->right, c);
        } else {
          l = llist_add(l, 0);
          l = llist_append(l, temp);
        }
        llist_node_free(temp->head);
        free(temp);
      } else if(root->right->ch < 0) {
        l = get_code(llist_add(l, 1), root->right, c);
      } else {
	      return l;
      }
    }
  }
  return l;
}

// put the ecode for each char in the array
llist* make_huff_table(int* freqtable, huff_tree_node* ht){
  llist* l = malloc(sizeof(llist)*256);
  for(int i=0; i<256; i++){
    llist* temp = new_llist();
    if(freqtable[i] == 0){
      l[i] = *temp;
    }else{
      l[i] = *(get_code(temp, ht, i));
    }
    free(temp);
  }
  return l;
}

int main(int argc, char** argv) {
  if(argc < 3) {
    printf("Expecting more arguments!\n");
  }
  int* freqTable;
  freqTable = make_freq_table(argv[1]);
  if(!freqTable) {
    printf("read file failed! :( \n");
    free(freqTable);
    exit(0);
  }
  FILE* orifile = fopen(argv[1],"r");
  FILE* newfile = fopen(argv[2], "w");
  if(!orifile){
    printf("cannot open file \n");
    exit(0);
  }
  fwrite(freqTable,4, 256, newfile);

  forest* forest = makeForest(new_forest(NULL), freqTable);
  huff_tree_node* htree = makeTree(forest);
  llist* huffTable = make_huff_table(freqTable, htree);
  int c = 1;
  int count = 0;
  llist* result = new_llist();
  while((c = fgetc(orifile)) > 0){
    llist* temp = &huffTable[c];
    result = llist_append(result,temp);
  }
  int bit_number = 0;
  if(result->size % 8 ==0){
    bit_number = result->size/8;
  }else{
    bit_number = result->size/8+1;
    while(result->size < bit_number * 8) {
      result = llist_add(result,0);
    }
  }
  int number = 0;
  if(result->size%8 == 0) {
    number = result->size / 8;
  } else {
    number = result->size / 8 + 1;
  }


  int* bitResult = malloc(sizeof(int) * number);
  int counter = 0;
  int i = 0;
  llist_node* cur = result->head;
  int j = 0;
  while(cur) {
    if(counter == 8) {
      j = 0;
      i ++;
      counter = 0;
    }
    j = j << 1;
    j = j | cur->data;
    bitResult[i] = j;
    cur = cur->next;
    counter ++;
  }

  for (int i = 0; i < number; i ++) {
      fwrite(bitResult + i,1, 1, newfile);
  }
  fclose(newfile);
  // free all the stuff
  for (int i = 0; i < 256; i++) {
    llist_node_free(huffTable[i].head);
  }
  free(huffTable);
  free_huff_tree(htree);
  forest_node_free(forest->head);
  free(forest);
  free(freqTable);
  llist_node_free(result->head);
  free(result);
  free(bitResult);
  return 0;
}
