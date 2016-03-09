//set.c
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "set.h"

//set_init
void set_init(Set *set, int (*match)(const void *key1, const void *key2),
              void (*destroy)(void *data))
{
    //initialize the set.
    list_init(set, destroy);
    set->match = match;
}

//set_insert
int set_insert(Set *set, const void *data)
{
    //don't allow the insertion of duplicates.
    if (set_is_member(set, data))
        return 1;

    //Insert the data.
    return list_ins_next(set, list_tail(set), data);
}

//set_remove
int set_remove(Set *set, void **data)
{
    ListElmt *member, *prev;

    //find the member to remove.
    prev = NULL;

    for (member = list_head(set); member != NULL; member = list_next(member))
    {
        if (set->match(*data, list_data(member)))
            break;
        prev = member;
    }
    // Return if the member was not found.
    if (member == NULL)
        return -1;

    //remove the member.
    return list_rem_next(set, prev, data);
}
//set_union
int set_union(Set *setu, const Set *set1, const Set *set2)
{
    ListElmt *member;
    void *data;

    //initialize the set for the union.
    set_init(setu, set1->match, NULL);

    //insert the members of the first set.
    for (member = list_head(set1); member != NULL; member = list_next(member))
    {
        data = list_data(member);
        if (list_ins_next(setu, list_tail(setu), data) != 0)
        {
            set_destroy(setu);
            return -1;
        }
    }

    //insert the member of the second set.
    for (member = list_head(set2); member != NULL; member = list_next(member))
    {
        if (set_is_member(set1, list_data(member)))
        {
            //don't allow the insertion of duplicates.
            continue;
        }
        else
        {
            data = list_data(member);
            if (list_ins_next(setu, list_tail(setu), data) != 0)
            {
                set_destroy(setu);
                return -1;
            }
        }
    }
    return 0;
}
