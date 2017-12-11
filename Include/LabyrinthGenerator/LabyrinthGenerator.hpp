#pragma once

#include <Utility/Random.hpp>

#include <cstdint>
#include <memory>

struct LabyrinthGenerator
{
    LabyrinthGenerator(const int32_t width, const int32_t height);
    LabyrinthGenerator(LabyrinthGenerator&) = delete;
    LabyrinthGenerator(LabyrinthGenerator&&) = delete;
    LabyrinthGenerator& operator=(LabyrinthGenerator&) = delete;
    LabyrinthGenerator& operator=(LabyrinthGenerator&&) = delete;

    bool IsWalled(const int32_t x, const int32_t y) const;

private:
    void ResetGrid() const;
    void SpawnStartAndEndLocation();
    void Visit(const int32_t x, const int32_t y);

    int32_t GetRandomIndexInQuadrant(const int32_t quadrant) const;
    bool IsInBounds(const int32_t x, const int32_t y) const;
    int32_t XYToIndex(const int32_t x, const int32_t y) const;

    Random m_Random;

    std::unique_ptr<unsigned char[]> m_Grid;

    int32_t m_Height;
    int32_t m_Width;
};
