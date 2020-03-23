#ifndef C_RANDOM_H
#define C_RANDOM_H

#include <stdint.h>

enum TypeofSeed {
        SEED_UNINITIALIZED,
        SEED_RDTSC,
        SEED_KEEP_USED,
        FORCE_RESEED
};

typedef struct Random {
        enum TypeofSeed initialized;
        uint64_t seed;

        int32_t (*Next)(void);
        int32_t (*NextBound)(int32_t floor, int32_t ceiling);
} Random;

Random RandomGenerator(enum TypeofSeed seedType);

#endif  // !C_RANDOM_H