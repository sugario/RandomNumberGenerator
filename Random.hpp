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

#pragma once

#include <cstdint>
#include <random>

class Random
{
 public:
    Random();
    explicit Random(const uint32_t seed);

    int32_t Next();
    int32_t Next(const int32_t ceiling);
    int32_t Next(const int32_t floor, const int32_t ceiling);

    double NextDouble();
    float NextFloat();

    template<class T>
    void ShuffleArray(T* arr, const uint32_t size);

 private:
     std::default_random_engine& global_urng();
     void Randomize();
     void Randomize(const uint32_t seed);
};

template void Random::ShuffleArray<int32_t>(int32_t* arr, uint32_t size);
template void Random::ShuffleArray<float>(float* arr, uint32_t size);
template void Random::ShuffleArray<double>(double* arr, uint32_t size);
template void Random::ShuffleArray<char>(char* arr, uint32_t size);
