#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *rem = (List*) malloc (sizeof(List));
  rem->head = NULL;
  rem->tail = NULL;
  rem->current = NULL;
  return rem;
}

void * firstList(List * list) {
  if(list->current == NULL)return NULL;
  
  list->current = list->head;
  return list->current->data;
}

void * nextList(List * list) {
  if(list->current == NULL)return NULL;
  if(list->current->next == NULL)return NULL;
  
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if(list->current == NULL)return NULL;
  
  list->current = list->tail;
  return list->current->data;
}

void * prevList(List * list) {
  if(list->current == NULL)return NULL;
  if(list->current->prev == NULL)return NULL;
  
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  Node *pizza = createNode(data);
  if(list->head != NULL)
  {
    pizza->next = list->head;
    list->head->prev = pizza;
    list->head = pizza;
  }
  else
  {
    list->current = pizza;
    list->head = pizza;
    list->tail = pizza;
  }
}

void pushBack(List * list, void * data) {
  list->current = list->tail;
  pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node *chirimoya = createNode(data);

  if(list->current == NULL)
  {
    list->current = chirimoya;
    list->head = chirimoya;
    list->tail = chirimoya;
  }
  
  if(list->current->next == NULL)
  {
    list->current->next = chirimoya;
    list->tail = chirimoya;
    chirimoya->prev = list->current;
  }
  else
  {
    chirimoya->next = list->current->next;
    list->current->next->prev = chirimoya;
    list->current->next = chirimoya;
    chirimoya->prev = list->current;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{
  void * save = list->current->data;
  
  if(list->current->prev == NULL)
  {
    list->current = list->current->next;
    free(list->head);
    list->head = list->current;
    list->head->prev = NULL;
    return save;
  }

  if(list->current->next == NULL)
  {
    list->current = list->current->prev;
    free(list->tail);
    list->tail = list->current;
    list->tail->next = NULL;
    return save;
  }
  
  /*if (list->current->prev == NULL){
    list->head = list->head->next;
    list->head->prev = NULL;
    return save;
  }

  if (list->current->next == NULL){
    list->tail = list->tail->prev;
    list->tail->next = NULL;
    return save;
  }*/

  return save;
  }

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}