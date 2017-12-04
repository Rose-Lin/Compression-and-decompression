#include <stdlib.h>
#include <stdio.h>
#include "forest_node.h"
#include "forest.h"

forest* new_forest(forest_node* head) {
  forest* new = malloc(sizeof(forest));
  new->head = head;
  if(head) {
    new->size = 1;
  } else {
    new->size = 0;
  }
  return new;
}

// insert to the end of the forest
forest* insert_after(forest* f, forest_node* target) {
  forest_node* cur = f->head;
  if(!cur) {
    f->head = target;
    f->size++;
  } else {
    for (int i = 1; i < f->size; i ++) {
      cur = cur->next;
    }
    cur->next = target;
    f->size ++;
  }
  return f;
}

void pop(forest* f) {
  if(!f->head) {
    printf("forest is empty\n");
  } else {
    forest_node* temp = f->head;
    f->head = temp->next;
    free(temp);
    f->size --;
  }
}

forest* ordInsert (forest* f, forest_node* node) {
  if(!f->head) {
    f = insert_after(f, node);
  } else {
    forest_node* temp = f->head;
    forest_node* after = temp->next;
    while (temp->val->freq < node->val->freq) {
      if (!after) {
        f = insert_after(f, node);
        break;
      } else if(after->val->freq < node->val->freq) {
        temp = after;
        after = after->next;
      } else {
        if(after->val->freq == node->val->freq) {
          if (after->val->ch > node->val->ch) {
            temp->next = node;
            node->next = after;
            f->size ++;
            break;
          } else {
            node->next = after->next;
            after->next = node;
            f->size ++;
            break;
          }
        } else {
          temp->next = node;
          node->next = after;
          f->size ++;
          break;
        }
      }
    }
  }
  return f;
}

void free_forest(forest* f){
    forest_node* node = f->head;
    forest_node_free(node);
    free(f);
}
