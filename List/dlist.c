#include "dlist.h"
//dlist_init
void dlist_init(DList *list, void (*destroy)(void *data))
{
    //initialize the list
    list->size = 0;
    list->destory = destroy;
    list->head = NULL;
    list->tail = NULL;

    return;
}
//dlist_destory
void dlist_destory(DList *list)
{
    void *data;
    //remove each element.
    while (dlist_size(list) > 0)
    {
        if (dlist_remove(list, dlist_tail(list), (void **)&data) == 0 &&
             list->destory != NULL)
        {
            //call a user-defined function to free dynamically allocted data.
            list->destory(data);
        }
    }
    //No operations are allowed now, but clear the structure a precaution
    memset(list, 0, sizeof(DList));
    return;
}
//list_ins_next
int dlist_ins_next(DList *list, DListElmt *element, const void **data)
{
    DListElmt *new_element;
    //do not allow a Null element unless the list is empty
    if (element == NULL && dlist_size(list) != 0)
        return -1;
    //allocate storage for the element.
    if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
        return -1;

    //insert the new element into the list.
    new_element->data = (void *)data;

    if(dlist_size(list) == 0)
    {
        //handle insertion when the list is empty
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_element;
    }else
    {
        //handle insertion when the list is not empty.
        new_element->next = element->next;
        new_element->prev = element;

        if (element->next == NULL)
            list->tail = new_element;
        else
            element->next->prev = new_element;

        element->next = new_element;
    }
    // adjust the size of the list to account for the inserted list
    list->size++;
    return 0;
}

//dlist_ins_prev
int dlist_ins_prev(DList *list, DListElmt *element, const void *data)
{
    DListElmt *new_element;

    //don't allow a NULL element unless the list is empty
    if (element == NULL && dlist_size(list) != 0)
        return -1;

    //allocate storage to be managed by the abstract datatype.
    if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
        return -1;

    //insert the new element into the list.
    new_element->data = (void *)data;
    if (dlist_size(list) == 0)
    {
        //handle insertion when the list is  empty
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_element;
    }
    else
    {
        //handle insertion when the list is not empty
        new_element->next = element;
        new_element->prev = element->prev;

        if (element->prev == NULL)
            list->head = new_element;
        else
            element->prev->next = new_element;

        element->prev = new_element;
    }
    //adjust the size of the list to account for the new element
    list->size++;
    return 0;
}

//dlist_remove
int dlist_remove(DList *list, DListElmt *element, void **data)
{
    //don't allow a NULL element or removal from an empty list.
    if (element == NULL || dlist_size(list) == 0)
        return -1;

    //remove the element from the list.
    *data = element->data;

    if (element == list->head)
    {
        //handle removal from the head of the list.
        list->head = element->next;

        if (list->head == NULL)
            list->tail = NULL;
        else
            element->next->prev = NULL;
    }
    else
    {
        //handle removal from other than the head of the list
        element->prev->next = element->next;
        if (element->next == NULL)
            list->tail = element->prev;
        else
            element->next->prev = element->prev;
    }
    //free the storage allocated by the abstract datatype.
    free(element);
    //adjust the size of the list to account for the remove element.
    list->size--;
    return 0;

}


