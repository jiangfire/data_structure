//clist.c
#include <stdlib.h>
#include <string.h>

#include "clist.h"

//clist_init
void clist_init(CList *list, void (*destroy)(void **data))
{
    //initialize the list
    list->size = 0;
    list->destory = destroy;
    list->head = NULL;

    return;
}

//clist_destroy
void clist_destroy(CList *list)
{
    void *data;

    //remove each element.
    while (clist_size(list) > 0)
    {
        if (clist_rem_next(list, list->head, (void **)&data) == 0 &&
             list->destory != NULL)
        {
            //call a user-defined function to free dynamically allocated data.
            list->destory(data);
        }
    }
    //no operation are allowed now, but clear the structure as a precaution
    memset(list, 0, sizeof(CList));
    return;
}
