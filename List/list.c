/* list.c */
#include <stdlib.h>
#include <string.h>

#include "list.h"

/* list_init */
void list_init(List *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;

    return;
}

/*list_destory*/

void list_destory(List *list)
{
    void *data;
    //Remove each element.
    while (list_size(list) > 0)
    {
        if(list_rem_next(list, NULL, (void **)&data) == 0 && list->destory != NULL)
        {
            list->destory(data);
        }
    }
    memset(list, 0, sizeof(list));
}

int list_ins_next(List *list, ListElmt *element, const void *data)
{
    ListElmt *new_element;
    if ((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL)
        return -1;
    new_element->data = (void *)data;
    if (element == NULL) //û�еĻ��Ͳ���ĩβ
    {
        if(list_size(list) == 0)
            list->tail = new_element;

        new_element->next = list->head;
        list->head = new_element;
    }
    else
    {
        if (element->next == NULL)
            list->tail = new_element;

        new_element->next = element->next;
        element->next = new_element;
    }
    list->size++;
    return 0;
}

int list_rem_next(List *list, ListElmt *element, void **data)
{
    ListElmt *old_element;
    //Do not allow removal from an empty list.
    if (list_size(list) == 0)
        return -1;
    //Remove the element from the list.
    if (element == NULL) //ɾ��ͷԪ��
    {
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next; //����ͷ����һ��Ԫ��

        if (list_size(list) == 1)
            list->tail = NULL;
    }
    else
    {
        //handle removal from somewhere other than head.
        if (element->next == NULL)
            return -1;
        *data = element->next->data; //ɾ�����Ԫ�ص���һ��Ԫ�أ����ص���data�����Բ����ͷ�
        old_element = element->next;//������޷��ͷ�
        element->next = element->next->next;

        if (element->next == NULL)
            list->tail = element;
    }

    //free the storage allocated by the abstract datatype.
    free(old_element);
    //adjust the size of the list to account for the removed element.
    list->size--;
    return 0;
}
