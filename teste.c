#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tsmst.h"

int main()
{
    mt_state state;
    mt_init(&state, time(NULL));

    // Generate 10 random numbers
    int i;
    for (i = 0; i < 10; i++)
    {
        unsigned long num = 1 + mt_next(&state) % 100;
        printf("%lu\n", num);
    }

    return 0;
}
