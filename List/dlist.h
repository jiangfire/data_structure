#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>

//Define a structure for double-linked list elements.
typedef struct DListElemt_
{
	void *data;
	struct DListElemt_ *prev;
	struct DListElemt_ *next;
} DListElmt;

//define a structure for doubly-linked lists.
typedef struct DList_
{
	int size;
	int (*match)(const void *key1, const void *key2);
	void (*destory)(void *data);
	DListElmt *head;
	DListElmt *tail;
} DList;

//public interface
void dlist_init(DList *list, void (*destory)(void *data));
void dlist_destory(DList *list);
int dlist_ins_next(DList *list, DListElmt *element, const void *data);
int dlist_ins_prev(DList *list, DListElmt *element, const void *data);
int dlist_remove(DList *list, DListElmt *element, void **data);

#define dlist_size(list) ((list)->size)
#define dlist_head(list) ((list)->head)
#define dlist_tail(list) ((list)->tail)
#define dlist_is_head(element) ((element)->prev == NULL ? 1:0)
#define dlist_is_tail(element) ((element)->next == NULL ? 1:0)
#define dlist_data(element) ((element)->data)
#define dlist_prev(element) ((element)->prev)
#define dlist_next(element) ((element)->next)

#endif // DLIST_H


