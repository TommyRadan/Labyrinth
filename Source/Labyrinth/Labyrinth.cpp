#include <algorithm>
#include <iostream>

#include "Labyrinth.h"

Labyrinth::Labyrinth()
{
    m_width = LabyrinthDefault::Width;
    m_height = LabyrinthDefault::Height;

    m_grid = new char[m_width * m_height];
}

Labyrinth::Labyrinth(const int32_t& width, const int32_t& height) : m_width(width), m_height(height)
{
    if ((m_width % 2) == 0)
    {
        m_width++;
    }

    if ((m_height % 2) == 0)
    {
        m_height++;
    }

    m_grid = new char[m_width * m_height];
}

Labyrinth::~Labyrinth()
{
    delete[] m_grid;
}

void Labyrinth::ResetGrid()
{
    for (int32_t i = 0; i < (m_width * m_height); i++)
    {
        m_grid[i] = '#';
    }
}

int32_t Labyrinth::GetRandomIndexInQuadrant(int32_t quadrant)
{
    int32_t x;
    int32_t y;

    int32_t minX = 0;
    int32_t maxX = m_width;

    int32_t minY = 0;
    int32_t maxY = m_height;

    switch (quadrant)
    {
        case 1:
            maxX = m_width / 2;
            maxY = m_height / 2;
            break;
        case 2:
            minX = m_width / 2;
            maxY = m_height / 2;
            break;
        case 3:
            minY = m_height / 2;
            maxX = m_width / 2;
            break;
        case 4:
            minX = m_width / 2;
            minY = m_height / 2;
            break;
        default:
            break;
    }

    do
    {
        x = rand() % (maxX - minX) + minX;
        y = rand() % (maxY - minY) + minY;
    } while (m_grid[XYToIndex(x, y)] != ' ');

    return XYToIndex(x, y);
}

void Labyrinth::SpawnStartAndEndLocation()
{
    int32_t startIndex;
    int32_t endIndex;
    int32_t quadrant[] = { 1, 2, 3, 4 };

    std::random_shuffle(quadrant, quadrant + 4);

    startIndex = GetRandomIndexInQuadrant(quadrant[0]);
    endIndex = GetRandomIndexInQuadrant(quadrant[1]);

    m_grid[startIndex] = 'S';
    m_grid[endIndex] = 'E';
}

int32_t Labyrinth::XYToIndex(const int32_t& x, const int32_t& y)
{
    return y * m_width + x;
}

bool Labyrinth::IsInBounds(const int32_t& x, const int32_t& y)
{
    if ((x < 0) || (x >= m_width))
    {
        return false;
    }

    if ((y < 0) || (y >= m_height))
    {
        return false;
    }

    return true;
}

void Labyrinth::Visit(const int32_t& x, const int32_t& y)
{
    int directions[] = { NORTH, EAST, SOUTH, WEST };
    std::random_shuffle(directions, directions + NUMBER_OF_DIRECTIONS);

    m_grid[XYToIndex(x, y)] = ' ';

    for (uint32_t i = 0; i < NUMBER_OF_DIRECTIONS; i++)
    {
        int32_t x2 = x;
        int32_t y2 = y;

        int32_t dx = 0;
        int32_t dy = 0;

        switch (directions[i])
        {
            case NORTH:
                dy = -1;
                break;
            case SOUTH:
                dy = 1;
                break;
            case EAST:
                dx = 1;
                break;
            case WEST:
                dx = -1;
                break;
            default:
                break;
        }

        x2 = x + (dx * 2);
        y2 = y + (dy * 2);

        if (IsInBounds(x2, y2) && (m_grid[XYToIndex(x2, y2)] == '#'))
        {
                m_grid[XYToIndex(x2 - dx, y2 - dy)] = ' ';
                Visit(x2, y2);
        }
    }
}

void Labyrinth::PrintGrid()
{
    for (int32_t y = 0; y < m_height; y++)
    {
        for (int32_t x = 0; x < m_width; x++)
        {
            std::cout << m_grid[XYToIndex(x, y)];
        }

        std::cout << "\n";
    }
}
