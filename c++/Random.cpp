/*
*
* Copyright 2017 Tino Melvan
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*/

#include "Random.hpp"

/**
 * \brief Initializes a new instance of the Random class.
 */
Random::Random()
{
    Randomize();
}

/**
 * \brief Initializes a new instance of the Random class, using the specified seed value.
 * \param seed: 32-but unsigned integer feeding an instance of default_random_engine
 */
Random::Random(const uint32_t seed)
{
    Randomize(seed);
}

/**
 * \brief Create a non-negative random integer.
 */
int32_t Random::Next() const
{
    return Next(0, INT32_MAX);
}

/**
 * \brief Create a non-negative random integer that is less than the specified ceiling.
 * \param ceiling: maximal 32-bit integer that can be created.
 */
int32_t Random::Next(const int32_t ceiling) const
{
    return Next(0, ceiling);
}

/**
 * \brief Create a random integer in range.
 * \param floor: minimal 32-bit integer that can be created.
 * \param ceiling: maximal 32-bit integer that can be created.
 */
int32_t Random::Next(const int32_t floor, const int32_t ceiling) const
{
    static std::uniform_int_distribution<> d {};
    using parm_t = decltype(d)::param_type;

    if (floor < ceiling)
    {
        return d(globalURNG(), parm_t { floor, ceiling });
    }

    return d(globalURNG(), parm_t { ceiling, floor });
}

/**
 * \brief Create a floating-point number that is greater than or equal to 0.0, and less than 1.0.
 */
double Random::NextDouble() const
{
    return static_cast<double>(Next()) / INT32_MAX;
}

/**
 * \brief Create a random floating-point number between 0.0 and 1.0.
 */
float Random::NextFloat() const
{
    return static_cast<float>(Next()) / INT32_MAX;
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
 * \param seed: an 32-bit unsigned integer value to be used as seed by the default_random_engine
 */
void Random::Randomize(const uint32_t seed) const
{
    globalURNG().seed(seed);
}
