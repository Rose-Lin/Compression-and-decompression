#ifndef FOREST_H_
#define FOREST_H_

#include <stdlib.h>
#include "forest_node.h"

typedef struct forest{
  forest_node* head;
  int size;
}forest;

forest* ordInsert (forest* f, forest_node* node);

forest* new_forest(forest_node* head);

forest* insert_after(forest* f, forest_node* target);

//forest_node* find(int ch, forest* f);

void pop(forest* f);

void free_forest(forest* f);

#endif
