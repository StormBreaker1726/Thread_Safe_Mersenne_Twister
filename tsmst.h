#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL
#define UPPER_MASK 0x80000000UL
#define LOWER_MASK 0x7fffffffUL

typedef struct
{
    unsigned long mt[N];
    int mti;
    pthread_mutex_t lock;
} mt_state;

void mt_init(mt_state *state, unsigned long seed);

unsigned long mt_next(mt_state *state);
