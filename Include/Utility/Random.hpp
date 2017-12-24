#pragma once

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

template <typename T, size_t Size>
void Random::ShuffleArray(T(&array)[Size])
{
    for (auto& element : array)
    {
        auto r = Next(0, Size - 1);
        std::swap(element, array[r]);
    }
}
