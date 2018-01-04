#pragma once

#include <Infrastructure/Random.hpp>

#include <cstdint>
#include <memory>

struct LabyrinthGenerator
{
    LabyrinthGenerator(int32_t width, int32_t height);
    LabyrinthGenerator(LabyrinthGenerator&) = delete;
    LabyrinthGenerator(LabyrinthGenerator&&) = delete;
    LabyrinthGenerator& operator=(LabyrinthGenerator&) = delete;
    LabyrinthGenerator& operator=(LabyrinthGenerator&&) = delete;

    bool IsGoblet(int32_t x, int32_t y) const;
    bool IsStart(int32_t x, int32_t y) const;
    bool IsWalled(int32_t x, int32_t y) const;

 private:
    void ResetGrid() const;
    void SpawnStartAndEndLocation();
    void Visit(int32_t x, int32_t y);

    int32_t GetRandomIndexInQuadrant(int32_t quadrant) const;
    bool IsInBounds(int32_t x, int32_t y) const;
    int32_t XYToIndex(int32_t x, int32_t y) const;

    Random m_Random;

    std::unique_ptr<unsigned char[]> m_Grid;

    int32_t m_Height;
    int32_t m_Width;
};
