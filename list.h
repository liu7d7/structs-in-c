#ifndef LIST_H
#define LIST_H

#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#define list(x) x*

typedef struct list_t {
  int64_t capacity;
  int64_t count;
  int64_t elementSize;
} list_t;

void* list_new(int count, int elementSize) {
  void* this = malloc(sizeof(list_t) + count * elementSize);
  ((list_t*)this)->capacity = count;
  ((list_t*)this)->count = 0;
  ((list_t*)this)->elementSize = elementSize;
  return this + sizeof(list_t);
}

void list_resize(void** this, int64_t newSize) {
  list_t* l = *this - sizeof(list_t);
  void* newThis = malloc(sizeof(list_t) + newSize * l->elementSize);
  memcpy(newThis, *this - sizeof(list_t), sizeof(list_t) + l->count * l->elementSize);
  free(*this - sizeof(list_t));
  *this = newThis + sizeof(list_t);
  l = newThis;
  l->capacity = newSize;
}

void list_ensureCapacity(void** this, int64_t count) {
  list_t* l = *this - sizeof(list_t);
  if (l->capacity < count) {
    int64_t newSize = l->capacity;
    while (newSize < count) {
      newSize *= 2;
    }
    list_resize(this, newSize);
  }
}

void list_add(void** this, void* element) {
  list_t* l = *this - sizeof(list_t);
  list_ensureCapacity(this, l->count + 1);
  l = *this - sizeof(list_t);
  memcpy(*this + l->count * l->elementSize, element, l->elementSize);
  l->count++;
}

void list_delete(void* this) {
  free(this - sizeof(list_t));
}

void list_clear(void* this) {
  list_t* l = this - sizeof(list_t);
  l->count = 0;
}

void list_pop(void* this) {
  list_t* l = this - sizeof(list_t);
  l->count--;
}

void list_remove(void* this, long index) {
  list_t* l = this - sizeof(list_t);
  memmove(this + index * l->elementSize, this + (index + 1) * l->elementSize, (l->count - index - 1) * l->elementSize);
  l->count--;
}

int64_t list_count(void* this) {
  list_t* l = this - sizeof(list_t);
  return l->count;
}

int64_t list_elementSize(void* this) {
  list_t* l = this - sizeof(list_t);
  return l->elementSize;
}

int64_t list_capacity(void* this) {
  list_t* l = this - sizeof(list_t);
  return l->capacity;
}

#define foreach(var, list) for (typeof(list) var = list; var < list + list_count(list); var++)

#endif //LIST_H
