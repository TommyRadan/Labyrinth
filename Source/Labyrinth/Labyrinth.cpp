#include <Labyrinth/Labyrinth.hpp>

#include <algorithm>

enum Direction
{
    NORTH ,
    EAST,
    SOUTH,
    WEST,
    NUMBER_OF_DIRECTIONS
};

Labyrinth::Labyrinth(const int32_t width, const int32_t height) :
        m_Width { width },
        m_Height { height }
{
    if ((m_Width % 2) == 0)
    {
        m_Width++;
    }

    if ((m_Height % 2) == 0)
    {
        m_Height++;
    }

    m_Grid = new char[m_Width * m_Height];

    ResetGrid();
    SpawnStartAndEndLocation();
}

Labyrinth::~Labyrinth()
{
    delete[] m_Grid;
}

bool Labyrinth::IsWalled(int32_t x, int32_t y)
{
    return (m_Grid[XYToIndex(x, y)] == '#');
}

void Labyrinth::ResetGrid()
{
    for (int32_t i = 0; i < (m_Width * m_Height); i++)
    {
        m_Grid[i] = '#';
    }
}

int32_t Labyrinth::GetRandomIndexInQuadrant(int32_t quadrant)
{
    int32_t x;
    int32_t y;

    int32_t minX = 0;
    int32_t maxX = m_Width;

    int32_t minY = 0;
    int32_t maxY = m_Height;

    switch (quadrant)
    {
        case 1:
            maxX = m_Width / 2;
            maxY = m_Height / 2;
            break;
        case 2:
            minX = m_Width / 2;
            maxY = m_Height / 2;
            break;
        case 3:
            minY = m_Height / 2;
            maxX = m_Width / 2;
            break;
        case 4:
            minX = m_Width / 2;
            minY = m_Height / 2;
            break;
        default:
            break;
    }

    do
    {
        x = rand() % (maxX - minX) + minX;
        y = rand() % (maxY - minY) + minY;
    }
    while (m_Grid[XYToIndex(x, y)] != ' ');

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

    m_Grid[startIndex] = 'S';
    m_Grid[endIndex] = 'E';
}

int32_t Labyrinth::XYToIndex(const int32_t x, const int32_t y)
{
    return y * m_Width + x;
}

bool Labyrinth::IsInBounds(const int32_t x, const int32_t y)
{
    if ((x < 0) || (x >= m_Width))
    {
        return false;
    }

    if ((y < 0) || (y >= m_Height))
    {
        return false;
    }

    return true;
}

void Labyrinth::Visit(const int32_t x, const int32_t y)
{
    int directions[] = { NORTH, EAST, SOUTH, WEST };
    std::random_shuffle(directions, directions + NUMBER_OF_DIRECTIONS);

    m_Grid[XYToIndex(x, y)] = ' ';

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

        if (IsInBounds(x2, y2) && (m_Grid[XYToIndex(x2, y2)] == '#'))
        {
                m_Grid[XYToIndex(x2 - dx, y2 - dy)] = ' ';
                Visit(x2, y2);
        }
    }
}
