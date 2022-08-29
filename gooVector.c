#include "GooVector.h"

int vec_init_f(GooVector* vec, unsigned int size, unsigned int element_size) {
	if (vec->size != 0) {
		vec_destroy(vec);
	}
	int i;
	vec->size = 0;
	vec->start = NULL;
	if (size == 0) {
		return 0;
	}
	if ((vec->start = (element*)malloc(sizeof(element))) == NULL) {
		return -1;
	}
	vec->start->item = malloc(element_size);
	vec->start->next = NULL;
	element* cur_element = vec->start;
	vec->size++;
	for (i = 1; i < size; i++) {
		if ((cur_element->next = (element*)malloc(sizeof(element))) == NULL) {
			vec_destroy(vec); 
			return -1;
		}
		if ((cur_element->next->item = malloc(element_size)) == NULL) {
			vec_destroy(vec);
			return -1;
		}
		cur_element->next->next = NULL;
		cur_element = cur_element->next;
		vec->size++;
	}
	return 0;
}

void* get_item_f(GooVector* vec, unsigned int index) {
	if (index > vec->size - 1) {
		return NULL;
	}

	int i;
	element* cur_element = vec->start;
	
	for (i = 0; i < index; i++) {
		cur_element = cur_element->next;
	}
	
	return cur_element->item;
}

int push_back_f(GooVector* vec, void* item) {
	if (vec->size == 0) {
		if((vec->start = (element*)malloc(sizeof(element))) == NULL) {
			return -1;
		}
		vec->start->next = NULL;
		vec->start->item = item;
		vec->size++;
		return 0;
	}

	int i;
	element* cur_element = vec->start;

	for (i = 1; i < vec->size; i++) {
		cur_element = cur_element->next;
	}

	if ((cur_element->next = (element*)malloc(sizeof(element))) == NULL) {
		return -1;
	}
	cur_element->next->item = item;
	cur_element->next->next = NULL;
	vec->size++;
	return 0;
}

int pop_back(GooVector* vec) {
	if (vec->size == 0) {
		return -1;
	}
	else if (vec->size == 1) {
		if (vec->start->item != NULL) {
			free(vec->start->item);
		}
		free(vec->start);
		vec->size--;
		return 0;
	}

	int i;
	element* cur_element = vec->start;
	
	for (i = 1; i < vec->size - 1; i++) {
		cur_element = cur_element->next;
	}
	
	if (cur_element->next->item != NULL) {
		free(cur_element->next->item);
	}
	
	free(cur_element->next);
	vec->size--;
	return 0;
}

int insert_f(GooVector* vec, void* item, unsigned int index) {
	if (vec->size < index) {
		return -1;
	}
	else if (index == 0) {
		element* temp = vec->start;
		if ((vec->start = (element*)malloc(sizeof(element))) == NULL) {
			return -1;	
		}
		vec->start->next = temp;
		vec->start->item = item;
		vec->size++;
		return 0;
	}

	int i;
	element* cur_element = vec->start, *temp;

	for (i = 1; i < index; i++) {
		 cur_element = cur_element->next;
	} 

	temp = cur_element->next;
	if ((cur_element->next = (element*)malloc(sizeof(element))) == NULL) {
		cur_element->next = temp;
		return -1;
	}
	cur_element->next->next = temp;
	cur_element->next->item = item;
	vec->size++;
	return 0;
}

int remove_item(GooVector* vec, unsigned int index) {
	if (vec->size - 1 < index) {
		return -1;
	}
	else if (index == 0) {
		element* temp = vec->start->next;
		if (vec->start->item != NULL) {
			free(vec->start->item);
		}
		free(vec->start);
		vec->start = temp;
		vec->size--;
		return 0;
	}
	
	int i;
	element* cur_element = vec->start, *temp;
	
	for (i = 1; i < index; i++) {
		cur_element = cur_element->next;
	}
	
	temp = cur_element->next->next;
	
	if (cur_element->next->item != NULL) {
		free(cur_element->next->item);
	}
	
	free(cur_element->next);
	cur_element->next = temp;
	vec->size--;
	return 0;
}

int vec_destroy(GooVector* vec) {
	int i;
	element* cur_element = NULL, *temp = vec->start;
	
	for (i = 0; i < vec->size; i++) {
		cur_element = temp;
		temp = cur_element->next;
		if (cur_element->item != NULL) {
			free(cur_element->item);
		}
		free(cur_element);
	}
	vec->size = 0;
	return 0;
}
