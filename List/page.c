#include "clist.h"
#include "page.h"

//replace page
int replace_page(CListElmt **current)
{
    //circle through the list of page until one is found to replace
    while (((Page *)(*current)->data)->reference != 0)
    {
        ((Page *)(*current)->data)->reference = 0;
        *current = clist_next(*current);
    }
    return ((Page *)(*current)->data)->number;

}
