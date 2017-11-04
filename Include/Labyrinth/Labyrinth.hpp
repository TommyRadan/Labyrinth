#pragma once

#include <cstdint>

enum LabyrinthDefault
{
    Height = 23,
    Width = 79
};

enum Direction
{
    NORTH = 0,
    EAST,
    SOUTH,
    WEST,
    NUMBER_OF_DIRECTIONS
};

class Labyrinth
{
 public:
     Labyrinth();
     Labyrinth(const int32_t& width, const int32_t& height);
     ~Labyrinth();

     void PrintGrid();
     void ResetGrid();
     void SpawnStartAndEndLocation();
     void Visit(const int32_t& x, const int32_t& y);

 private:
     int32_t GetRandomIndexInQuadrant(int32_t quadrant);
     bool IsInBounds(const int32_t& x, const int32_t& y);
     int32_t XYToIndex(const int32_t& x, const int32_t& y);

     char *m_grid;
     int32_t m_height;
     int32_t m_width;
};
