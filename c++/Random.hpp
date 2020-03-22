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

#ifndef CPP_RANDOM
#define CPP_RANDOM

#include <cstdint>
#include <random>

#include <algorithm>

class Random
{
 public:
        Random();
        explicit Random(uint32_t seed);

        int32_t Next() const;
        int32_t Next(int32_t ceiling) const;
        int32_t Next(int32_t floor, int32_t ceiling) const;

        double NextDouble() const;
        float NextFloat() const;

        template <typename T, size_t Size>
        void ShuffleArray(T(&array)[Size]);

 private:
        std::default_random_engine& globalURNG() const;
        void Randomize() const;
        void Randomize(uint32_t seed) const;
};

/**
 * \brief: Randomize the content of an array.
 * \tparam T: int, float, double or char
 * \tparam Size: Length of an array
 * \param array: Pointer to an array
 */
template <typename T, size_t Size>
void Random::ShuffleArray(T(& array)[Size])
{
        for (auto& element : array) {
                auto r = Next(0, Size - 1);
                std::swap(element, array[r]);
        }
}

#endif  // !CPP_RANDOM
