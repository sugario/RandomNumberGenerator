#include <stdlib.h>
#include <stdint.h>

#include "Random.h"

#define SRAND_DEFAULT_SEED      (1)

static int32_t __Next(void);
static int32_t __NextBound(int32_t floor, int32_t ceiling);

static uint64_t Rdtsc(void);

static uint64_t GenerateSeed(enum TypeofSeed seedType);

static Random __generator = {
        .typeInitialized = SEED_UNINITIALIZED,
        .seed = SRAND_DEFAULT_SEED,

        .Next = &__Next,
        .NextBound = &__NextBound
};

static int32_t __Next(void)
{
        return rand();
}

static int32_t __NextBound(int32_t floor, int32_t ceiling)
{
        return (rand() % (ceiling - floor + 1)) + floor;
}

static uint64_t Rdtsc(void)
{
        uint32_t lo;
        uint32_t hi;

        __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));

        return ((uint64_t)hi << 32) | lo;
}

static uint64_t GenerateSeed(enum TypeofSeed seedType)
{
        if (seedType == SEED_KEEP_USED ||
            seedType == __generator.typeInitialized) {
                return __generator.seed;
        }

        if (seedType == FORCE_RESEED) {
                seedType = __generator.typeInitialized;
        }

        switch (seedType) {
        case SEED_RDTSC:
                return Rdtsc();
        case SEED_UNINITIALIZED:
        default:
                return SRAND_DEFAULT_SEED;
        }
}

Random RandomGenerator(enum TypeofSeed seedType)
{
        uint64_t seed = GenerateSeed(seedType);
        if (seed != __generator.seed) {
                __generator.seed = seed;
                srand(seed);
        }

        if (seedType != SEED_KEEP_USED &&
            seedType != FORCE_RESEED) {
                __generator.typeInitialized = seedType;
        }

        return __generator;
}
