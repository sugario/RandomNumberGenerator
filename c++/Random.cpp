#include <cstdint>
#include <cstdlib>
#include <random>

#include "Random.hpp"

#define DEFAULT_MAX_RAND_VALUE  RAND_MAX

/**
 * \brief Initializes a new instance of the Random class.
 */
Random::Random()
{
        Randomize();
}

/**
 * \brief Initializes a new instance of the Random class, using the specified
 *        seed value.
 * \param seed: 32-but unsigned integer feeding an instance of
 *              default_random_engine
 */
Random::Random(uint32_t seed)
{
        Randomize(seed);
}

/**
 * \brief Create a non-negative random integer.
 */
int32_t Random::Next() const
{
        return Next(0, DEFAULT_MAX_RAND_VALUE);
}

/**
 * \brief Create a non-negative random integer that is less than the specified
 *        ceiling.
 * \param ceiling: maximal 32-bit integer that can be created
 */
int32_t Random::Next(int32_t ceiling) const
{
        return Next(0, ceiling);
}

/**
 * \brief Create a random integer in range.
 * \param floor: minimal 32-bit integer that can be created
 * \param ceiling: maximal 32-bit integer that can be created
 */
int32_t Random::Next(int32_t floor, int32_t ceiling) const
{
        static std::uniform_int_distribution<> d {};
        using parm_t = decltype(d)::param_type;

        if (floor < ceiling) {
                return d(globalURNG(), parm_t { floor, ceiling });
        }

        return d(globalURNG(), parm_t { ceiling, floor });
}

/**
 * \brief Create a floating-point number that is greater than or equal to 0.0,
 *        and less than 1.0.
 */
double Random::NextDouble() const
{
        return static_cast<double>(Next()) / DEFAULT_MAX_RAND_VALUE;
}

/**
 * \brief Create a random floating-point number between 0.0 and 1.0.
 */
float Random::NextFloat() const
{
        return static_cast<float>(Next()) / DEFAULT_MAX_RAND_VALUE;
}

/**
 * \brief Create an URNG (Uniform Random Number Generator).
 */
std::default_random_engine& Random::globalURNG() const
{
        static std::default_random_engine u {};
        return u;
}

/**
 * \brief Sets the shared URNG to an unpredictable state.
 */
void Random::Randomize() const
{
        static std::random_device rd {};
        globalURNG().seed(rd());
}

/**
 * \brief Sets the shared URNG to an unpredictable state.
 * \param seed: an 32-bit unsigned integer value to be used as seed by the
 *              default_random_engine
 */
void Random::Randomize(uint32_t seed) const
{
        globalURNG().seed(seed);
}
