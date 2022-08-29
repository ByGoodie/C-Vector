#ifndef GOOVECTOR_H
#define GOOVECTOR_H

#include <stdlib.h>

typedef struct element {
	struct element* next;
	void* item;
}element;

typedef struct GooVector {
	element* start;
	unsigned int size;
}GooVector;

int vec_init_f(GooVector* vec, unsigned int size, unsigned int element_size);
void* get_item_f(GooVector* vec, unsigned int index);
int push_back_f(GooVector* vec, void* item);
int pop_back(GooVector* vec);
int insert_f(GooVector* vec, void* item, unsigned int index);
int remove_item(GooVector* vec, unsigned int index);
int vec_destroy(GooVector* vec);

#define vec_init(vec, size, T) (vec_init_f(vec, size, sizeof(T)))
#define get_item(vec, index, T) (*((T*)get_item_f(vec, index)))
#define push_back(vec, item, T) (push_back_f(vec, &(*((T*)malloc(sizeof(T)) = item))))
#define insert(vec, item, index, T) (insert_f(vec, &(*((T*)malloc(sizeof(T)) = item)), index))

#endif
