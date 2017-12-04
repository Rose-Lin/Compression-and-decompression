#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huff_tree_node.h"
#include "llist_node.h"
#include "llist.h"
#include "forest.h"
#include "forest_node.h"

llist* getEncode(char* filename) {
  FILE* file = fopen(filename, "r");
  if(!file) {
    printf("Cannot open file for getEncode\n");
    return NULL;
  }
  llist* result = new_llist();
  int i = 256;
  int c;
  while (i > 0) {
    fread(&c,4,1,file);
    i --;
  }
  while (!feof(file)) {
    fread(&c, 1, 1, file);
    result = llist_add(result, c);
  }
  return result;
}

int* make_pfreq_table(char* filename){
  FILE* file = fopen(filename,"r");
  if(!file){
    printf("Cannot open file.\n");
    return NULL;
  }
  int* pfreq_table = malloc(sizeof(int)*256);
  fread(pfreq_table, 4, 256, file);
  return pfreq_table;
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
forest* pmakeForest(forest* f, int* ftable) {
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

huff_tree_node* pmakeTree(forest* f) {
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

llist* convert(llist_node* node) {
  int input = node->data;
  llist* result = new_llist();
  int count = 0;
  while (input != 0) {
    int mod = input % 2;
    result = llist_addFront(result, mod);
    input /= 2;
    count ++;
  }
  while (count < 8) {
    result = llist_addFront(result, 0);
    count ++;
  }
  return result;
}

int main(int argc, char** argv){
  if(argc < 3) {
    printf("Expecting more arguments\n");
  }
  char* file = argv[1];
  int* pfreq_table = make_pfreq_table(file);
  // get the encode result
  llist* encodeResult = getEncode(file);
  if(! pfreq_table) {
    printf("read file failed! :( \n");
    free(pfreq_table);
    exit(0);
  }

  if (!encodeResult) {
    printf("read in encode result failed! :( \n");
    free(encodeResult);
    exit(0);
  }

  forest* forest = pmakeForest(new_forest(NULL), pfreq_table);
  huff_tree_node* ptree = pmakeTree(forest);
  FILE* orifile = fopen(argv[1],"r");
  FILE* newfile = fopen(argv[2], "w");
  if(!orifile) {
    printf("cannot open file \n");
    exit(0);
  }

  llist* binaryResult = new_llist();
  llist_node* head = encodeResult->head;
  while(head) {
    llist* temp = convert(head);
    binaryResult = llist_append(binaryResult,temp);
    llist_node_free(temp->head);
    free(temp);
    head = head->next;
  }

  //get the number of chars inside of the string
  int counter = 0;
  for (int i = 0; i < 256; i++) {
    counter += pfreq_table[i];
  }
  llist_node* temp = binaryResult->head;

  while (counter > 0) {
    int c = 0;
    huff_tree_node* h = ptree;
    while(h->ch < 0) {
      if(temp->data == 1) {
        h = h->right;
        temp = temp->next;
      } else if (temp->data == 0) {
        h = h->left;
        temp = temp->next;
      }
    }
    c = h->ch;
    fprintf(newfile, "%c", c);
    counter --;
  }

  fclose(newfile);

  // all the frees
  free(pfreq_table);
  llist_node_free(binaryResult->head);
  free(binaryResult);
  free_huff_tree(ptree);
  free_forest(forest);
  llist_node_free(encodeResult->head);
  free(encodeResult);
  return 0;
}
