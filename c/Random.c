#include <stdlib.h>
#include <stdint.h>

#include <time.h>

#ifdef __unix__
#include <unistd.h>
#include <fcntl.h>
#endif

#include "Random.h"

#define SRAND_DEFAULT_SEED      (1U)
#define DEFAULT_MAX_RAND_VALUE  (RAND_MAX)

static void SeedSequenceGenerator(uint32_t seed);
static int32_t GetRandomInteger(void);

static int32_t __Next(void);
static int32_t __NextBound(int32_t floor, int32_t ceiling);
static double __NextDouble(void);
static float __NextFloat(void);

static uint32_t Rdtsc(void);
static uint32_t CurrentTime(void);

#ifdef __unix__
static uint32_t URandom(void);
#endif

static uint32_t GenerateSeed(enum TypeofSeed seedType);

static Random __generator = {
        .typeInitialized = SEED_UNINITIALIZED,
        .seed = SRAND_DEFAULT_SEED,

        .Next = &__Next,
        .NextBound = &__NextBound,

        .NextDouble = &__NextDouble,
        .NextFloat = &__NextFloat
};

static void SeedSequenceGenerator(uint32_t seed)
{
#ifdef __unix__
        srandom(seed);
#else
        srand(seed);
#endif
}

static int32_t GetRandomInteger(void)
{
#ifdef __unix__
        return random();
#else
        return rand();
#endif
}

static int32_t __Next(void)
{
        return GetRandomInteger();
}

static int32_t __NextBound(int32_t floor, int32_t ceiling)
{
        return (GetRandomInteger() % (ceiling - floor + 1)) + floor;
}

static double __NextDouble(void)
{
        return ((double)__Next()) / DEFAULT_MAX_RAND_VALUE;
}

static float __NextFloat(void)
{
        return ((float)__Next()) / DEFAULT_MAX_RAND_VALUE;
}

static uint32_t Rdtsc(void)
{
        uint32_t lo;

        __asm__ __volatile__("rdtsc" : "=a"(lo));

        return lo;
}

static uint32_t CurrentTime(void)
{
        return time(NULL);
}

#ifdef __unix__
static uint32_t URandom(void)
{
        uint32_t seed;

        int32_t urandom_dev = open("/dev/urandom", O_RDONLY);
        if (urandom_dev < 0) {
                return SRAND_DEFAULT_SEED;
        }

        if (read(urandom_dev, &seed, sizeof(uint32_t)) != sizeof(uint32_t)) {
                (void)close(urandom_dev);
                return SRAND_DEFAULT_SEED;
        }

        (void)close(urandom_dev);
        return seed;
}
#endif

static uint32_t GenerateSeed(enum TypeofSeed seedType)
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
        case SEED_CURRENT_TIME:
                return CurrentTime();
#ifdef __unix__
        case SEED_URANDOM_DEV:
                return URandom();
#endif
        case SEED_UNINITIALIZED:
        default:
                return SRAND_DEFAULT_SEED;
        }
}

Random RandomGenerator(enum TypeofSeed seedType)
{
        uint32_t seed = GenerateSeed(seedType);
        if (seed != __generator.seed) {
                __generator.seed = seed;
                SeedSequenceGenerator(seed);
        }

        if (seedType != SEED_KEEP_USED &&
            seedType != FORCE_RESEED) {
                __generator.typeInitialized = seedType;
        }

        return __generator;
}
