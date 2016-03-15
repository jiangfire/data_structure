//frame.c
#include <stdlib.h>
#include "list.h"

//alloc_frame
int alloc_frame(List *frames) //申请frame空间
{
    int frame_number, *data;
    if (list_size(frames) == 0)
        return -1;
    else
    {
        if (list_rem_next(frames, NULL, (void **)&data) != 0)
            return -1;
        else
        {
            //store the number of available frame.
            frame_number = *data;
            free(data);
        }
}
    return frame_number;
}
int free_frame(List *frames, int frame_number)
{
    int *data;
    //Allocate storage for the frame number.

    if((data = (int *)malloc(sizeof(int))) == NULL)
        return -1;

    //put the frame back in the list of available frames.
    *data = frame_number;

    if (list_ins_next(frames, NULL, data) != 0)
        return -1;

    return 0;
}
