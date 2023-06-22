#include "tsmst.h"

void mt_init(mt_state *state, unsigned long seed)
{
    state->mt[0] = seed;
    for (state->mti = 1; state->mti < N; state->mti++)
    {
        state->mt[state->mti] = (1812433253UL * (state->mt[state->mti - 1] ^ (state->mt[state->mti - 1] >> 30)) + state->mti);
    }
    pthread_mutex_init(&state->lock, NULL);
}

unsigned long mt_next(mt_state *state)
{
    pthread_mutex_lock(&state->lock);

    if (state->mti >= N)
    {
        int i;
        unsigned long x;

        for (i = 0; i < N - M; i++)
        {
            x = (state->mt[i] & UPPER_MASK) | (state->mt[i + 1] & LOWER_MASK);
            state->mt[i] = state->mt[i + M] ^ (x >> 1) ^ ((x & 1) * MATRIX_A);
        }

        for (; i < N - 1; i++)
        {
            x = (state->mt[i] & UPPER_MASK) | (state->mt[i + 1] & LOWER_MASK);
            state->mt[i] = state->mt[i + (M - N)] ^ (x >> 1) ^ ((x & 1) * MATRIX_A);
        }

        x = (state->mt[N - 1] & UPPER_MASK) | (state->mt[0] & LOWER_MASK);
        state->mt[N - 1] = state->mt[M - 1] ^ (x >> 1) ^ ((x & 1) * MATRIX_A);

        state->mti = 0;
    }

    unsigned long y = state->mt[state->mti++];
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    pthread_mutex_unlock(&state->lock);
    return y;
}
