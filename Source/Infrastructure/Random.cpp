#include "Infrastructure/Random.hpp"

Random::Random()
{
    Randomize();
}

Random::Random(const uint32_t seed)
{
    Randomize(seed);
}

int32_t Random::Next() const
{
    return Next(0, INT32_MAX);
}

int32_t Random::Next(const int32_t ceiling) const
{
    return Next(0, ceiling);
}

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

double Random::NextDouble() const
{
    return static_cast<double>(Next()) / INT32_MAX;
}

float Random::NextFloat() const
{
    return static_cast<float>(Next()) / INT32_MAX;
}

std::default_random_engine& Random::globalURNG() const
{
    static std::default_random_engine u {};
    return u;
}

void Random::Randomize() const
{
    static std::random_device rd {};
    globalURNG().seed(rd());
}

void Random::Randomize(const uint32_t seed) const
{
    globalURNG().seed(seed);
}
