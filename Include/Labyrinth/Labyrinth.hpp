#pragma once

#include <cstdint>

struct Labyrinth
{
    Labyrinth(int32_t width, int32_t height);
    Labyrinth(Labyrinth&) = delete;
    Labyrinth(Labyrinth&&) = delete;
    Labyrinth& operator=(Labyrinth&) = delete;
    Labyrinth& operator=(Labyrinth&&) = delete;
    ~Labyrinth();

    bool IsWalled(int32_t x, int32_t y);

private:
    void ResetGrid();
    void SpawnStartAndEndLocation();
    void Visit(const int32_t x, const int32_t y);

    int32_t GetRandomIndexInQuadrant(int32_t quadrant);
    bool IsInBounds(const int32_t x, const int32_t y);
    int32_t XYToIndex(const int32_t x, const int32_t y);

    char* m_Grid;
    int32_t m_Height;
    int32_t m_Width;
};
