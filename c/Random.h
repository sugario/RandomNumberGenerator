#ifndef C_RANDOM_H
#define C_RANDOM_H

#include <stdint.h>

enum TypeofSeed {
        SEED_UNINITIALIZED,
        SEED_RDTSC,
        SEED_CURRENT_TIME,

#ifdef __unix__
        SEED_URANDOM_DEV,
#endif

        SEED_KEEP_USED,
        FORCE_RESEED
};

typedef struct Random {
        enum TypeofSeed typeInitialized;
        uint32_t seed;

        int32_t (*Next)(void);
        int32_t (*NextBound)(int32_t floor, int32_t ceiling);

        double (*NextDouble)(void);
        float (*NextFloat)(void);
} Random;

Random RandomGenerator(enum TypeofSeed seedType);

#endif  // !C_RANDOM_H
